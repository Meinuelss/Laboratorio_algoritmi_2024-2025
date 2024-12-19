#include "unity.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>  // Inclusione necessaria per free e altre funzioni di allocazione

// Funzioni di supporto
int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (unsigned char)(*str++);
    }
    return hash;
}

// Variabili globali per i test
HashTable* table;

void setUp(void) {
    // Creazione della hash table per ogni test
    table = hash_table_create(string_compare, string_hash);
    TEST_ASSERT_NOT_NULL(table);
}

void tearDown(void) {
    // Pulizia della hash table dopo ogni test
    hash_table_free(table);
}

void test_hash_table_put_and_get(void) {
    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    *value1 = 1;
    *value2 = 2;

    hash_table_put(table, "key1", value1);
    hash_table_put(table, "key2", value2);

    TEST_ASSERT_EQUAL_INT(*value1, *(int*)hash_table_get(table, "key1"));
    TEST_ASSERT_EQUAL_INT(*value2, *(int*)hash_table_get(table, "key2"));
    TEST_ASSERT_NULL(hash_table_get(table, "key3")); // Chiave non esistente
}

void test_hash_table_contains_key(void) {
    int* value1 = malloc(sizeof(int));
    *value1 = 1;

    hash_table_put(table, "key1", value1);

    TEST_ASSERT_TRUE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key2"));
}

void test_hash_table_remove(void) {
    int* value1 = malloc(sizeof(int));
    *value1 = 1;

    hash_table_put(table, "key1", value1);
    hash_table_remove(table, "key1");

    TEST_ASSERT_FALSE(hash_table_contains_key(table, "key1"));
    TEST_ASSERT_NULL(hash_table_get(table, "key1"));
}

void test_hash_table_resize(void) {
    int values[100];

    for (int i = 0; i < 100; i++) {
        values[i] = i;
        char key[10];
        sprintf(key, "key%d", i);
        hash_table_put(table, strdup(key), &values[i]);
    }

    for (int i = 0; i < 100; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        int* value = (int*)hash_table_get(table, key);
        TEST_ASSERT_NOT_NULL(value);
        TEST_ASSERT_EQUAL_INT(values[i], *value);
    }
}

void test_hash_table_keyset(void) {
    int* value1 = malloc(sizeof(int));
    int* value2 = malloc(sizeof(int));
    *value1 = 1;
    *value2 = 2;

    hash_table_put(table, "key1", value1);
    hash_table_put(table, "key2", value2);

    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);

    // Test per verificare che le chiavi siano presenti nel keyset
    int found_key1 = 0, found_key2 = 0;
    for (int i = 0; i < hash_table_size(table); i++) {
        if (strcmp((char*)keys[i], "key1") == 0) {
            found_key1 = 1;
        }
        if (strcmp((char*)keys[i], "key2") == 0) {
            found_key2 = 1;
        }
    }
    TEST_ASSERT_TRUE(found_key1);
    TEST_ASSERT_TRUE(found_key2);

    free(keys);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_hash_table_put_and_get);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_resize);
    RUN_TEST(test_hash_table_keyset);

    return UNITY_END();
}
