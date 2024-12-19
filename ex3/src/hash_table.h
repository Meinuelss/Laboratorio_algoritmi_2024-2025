#ifndef HASH_TABLE_H
#define HASH_TABLE_H

char* strdup(const char* str);

/**
 * @brief Structure representing a node in the hash table.
 */
typedef struct HashNode {
    void* key; /**< Key of the node */
    void* value; /**< Value of the node */
    struct HashNode* next; /**< Pointer to the next node in the chain */
} HashNode;

/**
 * @brief Structure representing the hash table.
 */
typedef struct {
    HashNode** buckets; /**< Array of pointers to hash nodes */
    int bucket_count; /**< Number of buckets in the table */
    int size; /**< Number of elements in the table */
    int (*key_compare)(const void*, const void*); /**< Function to compare keys */
    unsigned long (*hash_function)(const void*); /**< Function to compute the hash value of a key */
} HashTable;

/**
 * @brief Creates a new hash table.
 *
 * @param key_compare Function to compare keys
 * @param hash_function Function to compute the hash value of a key
 * @return Pointer to the created hash table
 */
HashTable* hash_table_create(int (*key_compare)(const void*, const void*), unsigned long (*hash_function)(const void*));

/**
 * @brief Adds or updates a key-value pair in the hash table.
 *
 * @param table Pointer to the hash table
 * @param key Pointer to the key
 * @param value Pointer to the value
 */
void hash_table_put(HashTable* table, const void* key, const void* value);

/**
 * @brief Retrieves the value associated with a key in the hash table.
 *
 * @param table Pointer to the hash table
 * @param key Pointer to the key
 * @return Pointer to the value, or NULL if the key is not found
 */
void* hash_table_get(const HashTable* table, const void* key);

/**
 * @brief Checks if a key exists in the hash table.
 *
 * @param table Pointer to the hash table
 * @param key Pointer to the key
 * @return 1 if the key exists, 0 otherwise
 */
int hash_table_contains_key(const HashTable* table, const void* key);

/**
 * @brief Removes a key-value pair from the hash table.
 *
 * @param table Pointer to the hash table
 * @param key Pointer to the key
 */
void hash_table_remove(HashTable* table, const void* key);

/**
 * @brief Returns the number of key-value pairs in the hash table.
 *
 * @param table Pointer to the hash table
 * @return Number of key-value pairs in the table
 */
int hash_table_size(const HashTable* table);

/**
 * @brief Returns an array of all keys in the hash table.
 *
 * @param table Pointer to the hash table
 * @return Array of pointers to all keys in the table
 */
void** hash_table_keyset(const HashTable* table);

/**
 * @brief Frees the memory allocated for the hash table.
 *
 * @param table Pointer to the hash table
 */
void hash_table_free(HashTable* table);

#endif /* HASH_TABLE_H */
