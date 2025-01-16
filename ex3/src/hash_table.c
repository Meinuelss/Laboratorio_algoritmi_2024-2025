#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define INITIAL_BUCKET_COUNT 16
#define LOAD_FACTOR 0.75

char* strdup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char* copy = malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

HashNode* hash_node_create(void* key, void* value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (node == NULL) {
        fprintf(stderr, "ERRORE: Allocazione nodo hash fallita\n");
        exit(1);
    }
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

HashTable* hash_table_create(int (*key_compare)(const void*, const void*), unsigned long (*hash_function)(const void*)) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        return NULL;
    }
    table->buckets = (HashNode**)calloc(INITIAL_BUCKET_COUNT, sizeof(HashNode*));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->bucket_count = INITIAL_BUCKET_COUNT;
    table->size = 0;
    table->key_compare = key_compare;
    table->hash_function = hash_function;
    return table;
}

void hash_table_resize(HashTable* table) {
    int new_bucket_count = table->bucket_count * 2;
    HashNode** new_buckets = (HashNode**)calloc((size_t)new_bucket_count, sizeof(HashNode*));
    if (new_buckets == NULL) {
        return;
    }

    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node != NULL) {
            HashNode* next = node->next;
            unsigned long hash = table->hash_function(node->key);
            int bucket_index = (int)hash % new_bucket_count;
            node->next = new_buckets[bucket_index];
            new_buckets[bucket_index] = node;
            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->bucket_count = new_bucket_count;
}

void hash_table_put(HashTable* table, const void* key, const void* value) {
    unsigned long idx = table->hash_function(key) % (size_t)table->bucket_count;
    HashNode* current = table->buckets[idx];

    while (current) {
        if (table->key_compare(current->key, key) == 0) {
            (*(int*)current->value) += (*(int*)value);
            return;
        }
        current = current->next;
    }

    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = strdup((const char*)key);
    new_node->value = malloc(sizeof(int));
    *(int*)new_node->value = *(int*)value;
    new_node->next = table->buckets[idx];
    table->buckets[idx] = new_node;
    table->size++;
}


void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long idx = table->hash_function(key) % (size_t)table->bucket_count;
    HashNode* current = table->buckets[idx];

    while (current) {
        if (table->key_compare(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

void hash_table_remove(HashTable* table, const void* key) {
    unsigned long hash = table->hash_function(key);
    int bucket_index = (int)hash % table->bucket_count;
    HashNode* node = table->buckets[bucket_index];
    HashNode* prev = NULL;

    while (node != NULL) {
        if (table->key_compare(node->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[bucket_index] = node->next;
            } else {
                prev->next = node->next;
            }

            // Libera solo se allocati dinamicamente
            free(node->key);
            free(node->value);
            free(node);
            table->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}


int hash_table_size(const HashTable* table) {
    return table->size;
}

void** hash_table_keyset(const HashTable* table) {
void** keys = (void**)malloc((size_t)table->size * sizeof(void*));
    int index = 0;
    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node != NULL) {
            keys[index++] = node->key;
            node = node->next;
        }
    }
    return keys;
}

void hash_table_free(HashTable* table) {
    for (size_t i = 0; i < (size_t)table->bucket_count; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table); 
}



