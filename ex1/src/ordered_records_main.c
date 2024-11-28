#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ordered_records.h"
#include "unity.h"


#define FILE_INPUT "records.csv"
#define FILE_OUTPUT "sorted.csv"
#define INITIAL_SIZE 5
#define MAX_RECORDS 200000000

int (*cmp)(const void *, const void *);

typedef struct {
    int id;
    char field1[100];
    int field2;
    double field3;
} Record;

int compar_record_string(const void *a, const void *b) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;
    return strcmp(recordA->field1, recordB->field1);
}

int compar_record_int(const void *a, const void *b) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;
    return (recordA->field2 - recordB->field2);
}

int compar_record_float(const void *a, const void *b) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;
    if (recordA->field3 < recordB->field3) return -1;
    if (recordA->field3 > recordB->field3) return 1;
    return 0;
}



size_t read_records(FILE *infile, Record *records, size_t max_records) {
    size_t count = 0;
    while (fscanf(infile, "%d,%[^,],%d,%lf\n", &records[count].id, records[count].field1, &records[count].field2, &records[count].field3) == 4) {
        count++;
        if (count >= max_records) {
            fprintf(stderr, "Numero massimo di record raggiunto.\n");
            break;
        }

    }
    printf("Letti %zu records. \n", count);
    if (count == 0) {
        fprintf(stderr, "Nessun record letto.\n");
    }
    return count;
}

void choose_cmp(int field){
    if (field == 1)
        cmp = compar_record_string;
    else if (field == 2)
        cmp = compar_record_int;
    else
        cmp = compar_record_float;
}

void choose_algo(int algo, void **record_ptrs, size_t count){
    if (algo == 1) {
        merge_sort(record_ptrs, count, cmp);
    } else if (algo == 2) {
        quick_sort(record_ptrs, count, cmp);
    }
}

void write_records(size_t count, void **record_ptrs, FILE *outfile){
    for(size_t i = 0; i < count; i++){
        fprintf(outfile, "%d,%s,%d,%lf\n", ((Record *)record_ptrs[i])->id, ((Record *)record_ptrs[i])->field1, ((Record *)record_ptrs[i])->field2, ((Record *)record_ptrs[i])->field3);
    }
}

void sort_records(FILE *infile, FILE *outfile, int field, int algo) {
    Record *records = malloc(MAX_RECORDS * sizeof(Record));
    if (records == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per records.\n");
        return;
    }

    size_t count = read_records(infile, records, MAX_RECORDS);
    if (count == 0) {
        free(records);
        return;
    }

    void **record_ptrs = malloc(count * sizeof(void *));
    if (record_ptrs == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per record_ptrs.\n");
        free(records);
        return;
    }

    for (size_t i = 0; i < count; i++) {
        record_ptrs[i] = &records[i];
    }

    clock_t start, end;
    start = clock();

    choose_cmp(field);

    choose_algo(algo, record_ptrs, count);

    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    write_records(count, record_ptrs, outfile);
    printf("Tempo di esecuzione: %.2f secondi \n", time_taken);
    free(records);
    free(record_ptrs);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Uso: %s <file_input> <file_output> <campo> <algoritmo>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(FILE_INPUT, "r");
    if (infile == NULL) {
        fprintf(stderr, "Errore nell'aprire il file di input.\n");
        return 1; 
    }

    FILE *outfile = fopen(FILE_OUTPUT, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Errore nell'aprire il file di output.\n");
        fclose(infile);
        return 1;
    }

    int field = atoi(argv[3]);
    int algo = atoi(argv[4]);

    if (field < 1 || field > 3) {
    fprintf(stderr, "Campo non valido. Deve essere 1, 2 o 3.\n");
    fclose(infile);
    fclose(outfile);
    return 1;
    }
    if (algo < 1 || algo > 2) {
        fprintf(stderr, "Algoritmo non valido. Deve essere 1 o 2.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    sort_records(infile, outfile, field, algo);

    fclose(infile);
    fclose(outfile);
    return EXIT_SUCCESS;
}
