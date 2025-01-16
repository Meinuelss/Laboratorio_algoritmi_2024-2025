#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "graph.h"
#include "hash_table.h"

char* strdup(const char* str){
	size_t len = strlen(str) + 1;
	char* copy = malloc(len);
	if (copy){
		memcpy(copy, str, len);
	}
	return copy;
}

void read_csv_and_build_graph(FILE *file, Graph gr){
	char line[256];
	while (fgets(line, sizeof(line), file)){
		char* place1 = strtok(line, ",");
		char* place2 = strtok(NULL, ",");
		char* distance_str = strtok(NULL, ",");

		if (!place1 || !place2 || !distance_str){
			fprintf(stderr, "Errore: Riga malformata nel file CSV.\n");
			continue;
		}

		double distance = atof(distance_str);

		char* node1 = strdup(place1);
		char* node2 = strdup(place2);

		if (!graph_contains_node(gr, node1)){
			graph_add_node(gr, node1);
		} 
		else{
			free(node1);
		}

		if (!graph_contains_node(gr, node2)){
			graph_add_node(gr, node2);
		} 
		else{
			free(node2);
		}

		graph_add_edge(gr, place1, place2, &distance);
		graph_add_edge(gr, place2, place1, &distance);
	}
}

void write_bfs_result_to_file(FILE *file, void** bfs_result){
	for (int i = 0; bfs_result[i] != NULL; i++){
		fprintf(file, "%s\n", (char*)bfs_result[i]);
	}
}

void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)){
	if (!gr || !start || !graph_contains_node(gr, start)) return NULL;

	HashTable* visited = hash_table_create(compare, hash);
	if (!visited) return NULL;

	void** queue = malloc((size_t)graph_num_nodes(gr) * sizeof(void*));
	if (!queue){
		hash_table_free(visited);
		return NULL;
	}

	void** visited_order = malloc((size_t)graph_num_nodes(gr) * sizeof(void*));
	if (!visited_order) {
		free(queue);
		hash_table_free(visited);
		return NULL;
	}
	
	int front = 0;
	int back = 0;
	int	visited_count = 0;

	queue[back++] = start;
	hash_table_put(visited, start, (void*)1);
	
	while (front < back){
		void* current = queue[front++];
		visited_order[visited_count++] = current;
		
		void** neighbours_of_current = graph_get_neighbours(gr, current);
		int num_neighbours = graph_num_neighbours(gr, current);

		for (int i = 0; i < num_neighbours; i++){
			if (!hash_table_contains_key(visited, neighbours_of_current[i])){
				queue[back++] = neighbours_of_current[i];
				hash_table_put(visited, neighbours_of_current[i], (void*)1);
			}
		}
		free(neighbours_of_current);
	}

	free(queue);
	hash_table_free(visited);
	visited_order = realloc(visited_order, (size_t)visited_count * sizeof(void*));
	return visited_order;
}
