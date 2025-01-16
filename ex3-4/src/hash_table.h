#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

typedef struct HashNode
	{
    void* key;
	void* value;
	struct HashNode* next;
	} HashNode;


typedef struct HashTable
	{
    HashNode** buckets;
	size_t capacity;
	size_t size;
	int (*cmp)(const void*, const void*);
	unsigned long (*hash)(const void*);
	} HashTable;

/**
 * @brief Creates a new empty hash table, but to create it, it needs to know how to compare two keys (e.g., use strcmp for strings or subtraction for integers)
 * and how to determine the hash index (always based on the key type, for example, for strings it works like this, for integers it's determined like this).
 * 
 * @param compare: Pointer to a function that compares two keys using strcmp. Must return 0 if the keys are equal, 1 if they are different.
 * @param hash: Pointer to a function that calculates a hash value based on the key type.
 * @return Returns a pointer to the new hash table. If it is NULL, it means memory allocation failed.
 */
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

/**
 * @brief Inserts a <key><value> pair into the hash table. If the key already exists, the value (frequency) 
 * associated with that key is updated by incrementing it by 1.
 * 
 * @param table: Pointer to the hash table.
 * @param key: Contains the key.
 * @param value: Contains the value.
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief Checks if the key is already present in the hash table, if it is present, it returns the associated value.
 * 
 * @param table: Pointer to the hash table.
 * @param key: Key to search for.
 * @return If the key exists, returns the value of that key; otherwise, NULL.
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief Simply checks whether a key is present in the hash table or not.
 * What is the purpose if we already have the get function? It is used to quickly check if the key in question exists without necessarily having to return a value (e.g., it can be useful in the remove function).
 * 
 * @param table: Pointer to the hash table.
 * @param key: Key to search for.
 * @return Returns 1 if the key is present, 0 otherwise.
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief Removes a <key><value> pair from the hash table; if the key does not exist, the function does nothing.
 * 
 * @param table: Pointer to the hash table.
 * @param key: Key to remove.
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief Returns the number of <key><value> pairs currently in the hash table.
 * 
 * @param table: Pointer to the hash table.
 * @return Returns the total number of elements in the table.
 */
int hash_table_size(const HashTable* table);

/**
 * @brief Returns an array containing all the <keys> (without the associated value) in the hash table, 
 * used to provide an overview of the keys currently stored in the table.
 * 
 * @param table: Pointer to the hash table.
 * @return Returns an array of pointers to the keys; returns NULL if the table is empty.
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief Frees the memory occupied by the hash table.
 * 
 * @param table: Pointer to the hash table to be freed.
 */
void hash_table_free(HashTable* table);

#endif // HASH_TABLE_H
