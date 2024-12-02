#include <stdio.h>
#include <stdlib.h>
#include "distance.h"
#include "unity.h"

static void test_edit_distance_null_string(void) {
    TEST_ASSERT_EQUAL_INT(0,edit_distance(NULL, NULL));
    TEST_ASSERT_EQUAL_INT(4,edit_distance(NULL, "casa"));
    TEST_ASSERT_EQUAL_INT(4,edit_distance("casa", NULL));
}

static void test_edit_distance_empty_string(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance("", ""));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("", "casa"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("casa", ""));
}

static void test_edit_distance_optimal_case(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance("laboratorio", "laboratorio"));
}

static void test_edit_distance_average_case(void) {
    TEST_ASSERT_EQUAL_INT(3, edit_distance("algoritmi", "altoritmin"));
    TEST_ASSERT_EQUAL_INT(3, edit_distance("algoritmi", "algori"));
    TEST_ASSERT_EQUAL_INT(3, edit_distance("algori", "algoritmi"));
}

static void test_edit_distance_worst_case(void) {
    TEST_ASSERT_EQUAL_INT(12, edit_distance("abcdef", "ghijkl"));
    TEST_ASSERT_EQUAL_INT(6, edit_distance("abcdef", "abcdefghilmn"));
    TEST_ASSERT_EQUAL_INT(6, edit_distance("abcdefghijkl", "ghijkl"));
}


static void test_edit_distance_dyn_null_string(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(NULL, NULL));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn(NULL, "casa"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("casa", NULL));
}

static void test_edit_distance_dyn_empty_string(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("", ""));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("", "pane"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn("pane", ""));
}

static void test_edit_distance_dyn_optimal_case(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn("laboratorio", "laboratorio"));
}

static void test_edit_distance_dyn_average_case(void) {
    TEST_ASSERT_EQUAL_INT(3, edit_distance_dyn("algoritmi", "altoritmin"));
    TEST_ASSERT_EQUAL_INT(3, edit_distance_dyn("algoritmi", "algori"));
    TEST_ASSERT_EQUAL_INT(3, edit_distance_dyn("algori", "algoritmi"));
}

static void test_edit_distance_dyn_worst_case(void) {
    TEST_ASSERT_EQUAL_INT(12, edit_distance_dyn("abcdef", "ghijkl"));
    TEST_ASSERT_EQUAL_INT(6, edit_distance_dyn("abcdef", "abcdefghilmn"));
    TEST_ASSERT_EQUAL_INT(6, edit_distance_dyn("abcdefghijkl", "ghijkl"));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_edit_distance_null_string);
    RUN_TEST(test_edit_distance_empty_string);
    RUN_TEST(test_edit_distance_optimal_case);
    RUN_TEST(test_edit_distance_average_case);
    RUN_TEST(test_edit_distance_worst_case);
    RUN_TEST(test_edit_distance_dyn_null_string);
    RUN_TEST(test_edit_distance_dyn_empty_string);
    RUN_TEST(test_edit_distance_dyn_optimal_case);
    RUN_TEST(test_edit_distance_dyn_average_case);
    RUN_TEST(test_edit_distance_dyn_worst_case);

    return UNITY_END();
}

