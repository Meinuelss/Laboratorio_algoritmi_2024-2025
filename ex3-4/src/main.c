#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "graph.h"
#include "hash_table.h"
#include "bfs.h"

unsigned long string_hash(const void* key){
	const char* str = (const char*)key;
	unsigned long hash = 5381;
	while (*str){
		hash = ((hash << 5) + hash) + (unsigned char)*str++;
	}
	return hash;
}

int string_compare(const void* a, const void* b){
	return strcmp((const char*)a, (const char*)b);
}

void normalize_string(char* word) {
	int j = 0;

	for (int i = 0; word[i] != '\0'; i++){
		if (word[i] == '-'){
			if (j > 0){
				word[j] = '\0';
				return;
			}
		}
		else if (isalpha((unsigned char)word[i])){
				word[j++] = (char)tolower((unsigned char)word[i]);
		}
	}
	if (j > 0){
		word[j] = '\0';
	}
}

int main(int argc, char** argv){
	if (argc != 4){
		printf("Uso: %s <file_csv> <nodo_partenza> <file_output>\n", argv[0]);
		return 1;
	}

	const char* input_file = argv[1];
	char start_node[256];
	strncpy(start_node, argv[2], sizeof(start_node) - 1);
	start_node[sizeof(start_node) - 1] = '\0';
	const char* output_file = argv[3];

	normalize_string(start_node);
	printf("Nodo di partenza normalizzato: '%s'\n", start_node);

	FILE* infile = fopen(input_file, "r");
	if (!infile){
		printf("\nErrore: il file CSV '%s' non esiste.\n", input_file);
		return 1;
	}

	Graph gr = graph_create(1, 0, string_compare, string_hash);
	if (!gr) {
		printf("\nErrore nella creazione del grafo.\n");
		fclose(infile);
		return 1;
	}

	read_csv_and_build_graph(infile, gr);

	clock_t start_time = clock();
	void** bfs_result = breadth_first_visit(gr, start_node, string_compare, string_hash);
	if (!bfs_result){
		printf("\nErrore: BFS non è riuscita o nodo di partenza '%s' non trovato.\n", start_node);
		graph_free(gr);
		fclose(infile);
		return 1;
	}

	

	FILE* outfile = fopen(output_file, "w");
    if (!outfile){
		printf("\nErrore: impossibile scrivere nel file di output '%s'.\n", output_file);
		free(bfs_result);
		graph_free(gr);
		fclose(infile);
		return 1;
	}
	write_bfs_result_to_file(outfile, bfs_result);

	clock_t end_time = clock();
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	free(bfs_result);
	graph_free(gr);
	fclose(infile);
	fclose(outfile);

	printf("Tempo di esecuzione: %.4f secondi\n", elapsed_time);

	return 0;
	}
