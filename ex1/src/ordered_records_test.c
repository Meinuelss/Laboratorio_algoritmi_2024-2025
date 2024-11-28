#include <stdio.h>
#include <stdlib.h>
#include "ordered_records.h"
#include "unity.h"


static int compar_int(const void* i1_p, const void* i2_p) {
    const int* int1_p = (const int*)i1_p;
    const int* int2_p = (const int*)i2_p;
    if (*int1_p > *int2_p) return 1;
    else if(*int1_p == *int2_p) return 0;
    else return -1;
}

static int i1, i2, i3, i4, i5, i6, i7, i8;
static OrderedArray *ordered_array;

void setUp(void) {
    i1 = -12;
    i2 = 0;
    i3 = 4;
    i4 = 2;
    i5 = 7;
    i6 = 10;
    i7 = 1;
    i8 = 6;
    ordered_array = ordered_array_create(compar_int);
}

static void test_empty_orderd_array(void){
    void **a[1] = {NULL};
    void **b[1] = {NULL};
    TEST_ASSERT_NULL(b[0]);
    TEST_ASSERT_NULL(a[0]);
}

static void test_null_ordered_array(void){
    void **a = NULL;
    void **b = NULL;
    merge_sort(a, 0, compar_int);
    quick_sort(b, 0, compar_int);
    TEST_ASSERT_NULL(b);
    TEST_ASSERT_NULL(a);
}

static void test_average_merge_sort(void) {

    void **array = malloc(sizeof(void*)* 8);
    array[0] = &i7;
    array[1] = &i2;
    array[2] = &i5;
    array[3] = &i6;
    array[4] = &i1;
    array[5] = &i3;
    array[6] = &i8;
    array[7] = &i4;

    size_t size = 8;
    
    merge_sort(array, size, compar_int);

    int* expected[] = {&i1, &i2, &i7, &i4, &i3, &i8, &i5, &i6}; // Ordine previsto

    TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, size);

}

//caso medio valido anche come caso migliore
static void test_average_quick_sort(void) {

    void **array = malloc(sizeof(void*)* 8);
    array[0] = &i7;
    array[1] = &i2;
    array[2] = &i5;
    array[3] = &i6;
    array[4] = &i1;
    array[5] = &i3;
    array[6] = &i8;
    array[7] = &i4;

    size_t size = 8;
    
    quick_sort(array, size, compar_int);

    int* expected[] = {&i1, &i2, &i7, &i4, &i3, &i8, &i5, &i6};

    TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, size);

}

static void test_worst_case_merge(void){
    //array al contrario
    int* expected[] = {&i1, &i2, &i7, &i4, &i3, &i8, &i5, &i6};
    void **array = malloc(sizeof(void*)* 8);
    array[0] = &i6;
    array[1] = &i5;
    array[2] = &i8;
    array[3] = &i3;
    array[4] = &i4;
    array[5] = &i7;
    array[6] = &i2;
    array[7] = &i1;

    size_t size = 8;

    merge_sort(array, size, compar_int);

    TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, size);
}

static void test_worst_case_quick(void){
    //array ordinato
    int* expected[] = {&i1, &i2, &i7, &i4, &i3, &i8, &i5, &i6};
    void **array = malloc(sizeof(void*)* 8);

    array[0] = &i1;
    array[1] = &i2;
    array[2] = &i7;
    array[3] = &i4;
    array[4] = &i3;
    array[5] = &i8;
    array[6] = &i5;
    array[7] = &i6;

    size_t size = 8;
    quick_sort(array, size, compar_int);

    TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, size);
}

static void test_best_case_merge(void){
    //array ordinato
    int* expected[] = {&i1, &i2, &i7, &i4, &i3, &i8, &i5, &i6};
    void **array = malloc(sizeof(void*)* 8);
    array[0] = &i1;
    array[1] = &i2;
    array[2] = &i7;
    array[3] = &i4;
    array[4] = &i3;
    array[5] = &i8;
    array[6] = &i5;
    array[7] = &i6;

    size_t size = 8;

    merge_sort(array, size, compar_int);

    TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, size);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_orderd_array);
    RUN_TEST(test_null_ordered_array);
    RUN_TEST(test_average_merge_sort);
    RUN_TEST(test_average_quick_sort);
    RUN_TEST(test_worst_case_merge);
    RUN_TEST(test_worst_case_quick);
    RUN_TEST(test_best_case_merge);

    return UNITY_END();
}
