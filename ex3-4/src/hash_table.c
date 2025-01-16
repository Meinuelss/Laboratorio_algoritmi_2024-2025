#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "bfs.h"

#define INITIAL_CAPACITY 16

HashTable* hash_table_create(int (*f1)(const void*, const void*), unsigned long (*f2)(const void*)){
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	if(table==NULL){
		return NULL;
	}
	table->capacity = INITIAL_CAPACITY;
	table->size = 0;
	table->cmp = f1;
	table->hash = f2;
	table->buckets = (HashNode**)calloc(table->capacity, sizeof(HashNode*));
	return table;
}

void hash_table_put(HashTable* table, const void* key, const void* value){
	if (!table || !key) return;

	if ((float)table->size / (float)table->capacity > 0.75){
		size_t new_capacity = table->capacity * 2;
		HashNode** new_buckets = (HashNode**)calloc(new_capacity, sizeof(HashNode*));
		if (!new_buckets) return;

		for (size_t i = 0; i < table->capacity; i++){
			HashNode* current = table->buckets[i];
			while (current){
				size_t new_idx = (unsigned long)table->hash(current->key) % new_capacity;

				HashNode* next = current->next;
				current->next = new_buckets[new_idx];
				new_buckets[new_idx] = current;

				current = next;
			}
		}

		free(table->buckets);
		table->buckets = new_buckets;
		table->capacity = new_capacity;
	}

	size_t idx = (unsigned long)table->hash(key) % table->capacity;
	HashNode* current = table->buckets[idx];

	while (current){
		if (table->cmp(current->key, key) == 0){
			current->value = (void*)value;
			return;
		}
		current = current->next;
	}

	HashNode* newNode = malloc(sizeof(HashNode));
	if (!newNode) return;
	
	newNode->key = (void*)key;
	newNode->value = (void*)value;
	newNode->next = table->buckets[idx];
	table->buckets[idx] = newNode;
	table->size++;
}

void* hash_table_get(const HashTable* table, const void* key){
	if (!table || !key) return NULL;

	unsigned long idx = table->hash(key) % (unsigned long)table->capacity;
	HashNode* current = table->buckets[idx];
	
	while(current){
		if (table->cmp(current->key, key) == 0){
			return current->value;
		}
		current = current->next;
	}

	return NULL;
}

int hash_table_contains_key(const HashTable *table, const void *key){
	unsigned long idx = table->hash(key) % (unsigned long)table->capacity;
	HashNode *current = table->buckets[idx];

	while (current != NULL){
		if (table->cmp(current->key, key) == 0){
			return 1;
		}
		current = current->next;
	}

	return 0;
}

void hash_table_remove(HashTable* table, const void* key){
	if (!table || !key) return;
	
	unsigned long idx = table->hash(key) % (unsigned long)table->capacity;
	HashNode* current = table->buckets[idx];
	HashNode* prev = NULL;

	while(current){
		if (table->cmp(current->key, key) == 0){
			if (prev){
				prev->next = current->next;
			} 
			else{
				table->buckets[idx] = current->next;
			}
			free(current);
			table->size--;
			return;
		}
		prev=current;
		current=current->next;
	}
}

int hash_table_size(const HashTable *table){
	return (int)table->size;
}

void** hash_table_keyset(const HashTable* table){
	void** keys = (void**)malloc(table->size * sizeof(void*));
	size_t index = 0;

	for (size_t i = 0; i < table->capacity; i++){
		HashNode* current = table->buckets[i];
		while(current)
		{
			keys[index++] = current->key;
			current = current->next;
		}
	}

	return keys;
}

void hash_table_free(HashTable* table){
	for (size_t i = 0; i < table->capacity; i++){
		HashNode* current = table->buckets[i];
		while (current){
			HashNode* next = current->next;
			free(current);
			current = next; 
		}
	}
	free(table->buckets);
	free(table);
}
