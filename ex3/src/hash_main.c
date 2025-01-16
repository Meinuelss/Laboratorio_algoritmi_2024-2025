#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

int compare(const void* a, const void* b){
    return strcmp((const char*)a, (const char*)b);
}

unsigned long string_hash(const void* key){
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + (size_t)c;
    }
    return hash;
}

void normalize_string(char* word){
    int j = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '-' || ((unsigned char)word[i] == 0xE2 && (unsigned char)word[i + 1] == 0x80 && (unsigned char)word[i + 2] == 0x94)){
            if (j > 0) {
                word[j] = '\0';
                j = 0;
            }
        }else if (isalpha(word[i])){
                word[j++] = (char)tolower(word[i]);
        }
    }

    if (j > 0){
        word[j] = '\0';
        }
    }


// Funzione principale
char* find_most_frequent_word(HashTable* table, int min_length) {
    char* most_frequent = NULL;
    int max_frequency = 0;

    for (size_t i = 0; i < (size_t)table->bucket_count; i++){
        HashNode* current = table->buckets[i];
        while (current){
            if (strlen((const char*)current->key) >= (size_t)min_length) {
                int frequency = *(int*)current->value;
                if (frequency > max_frequency) {
                    max_frequency = frequency;
                    most_frequent = (char*)current->key;
                }
            }
            current = current->next;
        }
    }
    return most_frequent;
}

void populate_hash_table(const char* file_path, int min_length, HashTable* table){

    FILE* file = fopen(file_path, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char word[256];
    while (fscanf(file, "%255s", word) == 1){
        normalize_string(word);

        if (strlen(word) >= (size_t)min_length){
            int* value = (int*)malloc(sizeof(int));
            *value = 1;
            hash_table_put(table, word, value);
        }
    }
    fclose(file);

}

int main(int argc, char* argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file_path> <min_word_length>\n", argv[0]);
        return 1;
    }

    const char* file_path = argv[1];
    int min_length = atoi(argv[2]);

    HashTable* table = hash_table_create(compare, string_hash);
    populate_hash_table(file_path, min_length, table);

    char* most_frequent = find_most_frequent_word(table, min_length);
    if (most_frequent){
        printf("Most frequent word: '%s'\n", most_frequent);
    }else{
        printf("No words found with minimum length %d.\n", min_length);
    }

    hash_table_free(table);
    return 0;
}

