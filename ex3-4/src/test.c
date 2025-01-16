#include "unity.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

int compare_ints(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

unsigned long hash_int(const void *key) {
    return (unsigned long)(*(int *)key);
}

Graph gr_labelled_directed;
Graph gr_labelled_undirected;
Graph gr_unlabelled_directed;
Graph gr_unlabelled_undirected;

void setUp(void) {
    gr_labelled_directed = graph_create(1, 1, compare_ints, hash_int);
    gr_labelled_undirected = graph_create(1, 0, compare_ints, hash_int);
    gr_unlabelled_directed = graph_create(0, 1, compare_ints, hash_int);
    gr_unlabelled_undirected = graph_create(0, 0, compare_ints, hash_int);

    TEST_ASSERT_NOT_NULL(gr_labelled_directed);
    TEST_ASSERT_NOT_NULL(gr_labelled_undirected);
    TEST_ASSERT_NOT_NULL(gr_unlabelled_directed);
    TEST_ASSERT_NOT_NULL(gr_unlabelled_undirected);
}

void tearDown(void) {
    graph_free(gr_labelled_directed);
    graph_free(gr_labelled_undirected);
    graph_free(gr_unlabelled_directed);
    graph_free(gr_unlabelled_undirected);
}

void test_graph_creation(void) {
    TEST_ASSERT_EQUAL(1, graph_is_labelled(gr_labelled_directed));
    TEST_ASSERT_EQUAL(1, graph_is_directed(gr_labelled_directed));

    TEST_ASSERT_EQUAL(1, graph_is_labelled(gr_labelled_undirected));
    TEST_ASSERT_EQUAL(0, graph_is_directed(gr_labelled_undirected));

    TEST_ASSERT_EQUAL(0, graph_is_labelled(gr_unlabelled_directed));
    TEST_ASSERT_EQUAL(1, graph_is_directed(gr_unlabelled_directed));

    TEST_ASSERT_EQUAL(0, graph_is_labelled(gr_unlabelled_undirected));
    TEST_ASSERT_EQUAL(0, graph_is_directed(gr_unlabelled_undirected));
}

void test_add_and_check_nodes(void) {
    int node1 = 1, node2 = 2;

    TEST_ASSERT_TRUE(graph_add_node(gr_labelled_directed, &node1));
    TEST_ASSERT_TRUE(graph_add_node(gr_labelled_directed, &node2));
    TEST_ASSERT_FALSE(graph_add_node(gr_labelled_directed, &node1));

    TEST_ASSERT_TRUE(graph_contains_node(gr_labelled_directed, &node1));
    TEST_ASSERT_TRUE(graph_contains_node(gr_labelled_directed, &node2));

    TEST_ASSERT_TRUE(graph_add_node(gr_labelled_undirected, &node1));
    TEST_ASSERT_TRUE(graph_add_node(gr_labelled_undirected, &node2));
    TEST_ASSERT_FALSE(graph_add_node(gr_labelled_undirected, &node1));

    TEST_ASSERT_TRUE(graph_contains_node(gr_labelled_undirected, &node1));
    TEST_ASSERT_TRUE(graph_contains_node(gr_labelled_undirected, &node2));

    TEST_ASSERT_TRUE(graph_add_node(gr_unlabelled_directed, &node1));
    TEST_ASSERT_TRUE(graph_add_node(gr_unlabelled_directed, &node2));
    TEST_ASSERT_FALSE(graph_add_node(gr_unlabelled_directed, &node1));

    TEST_ASSERT_TRUE(graph_contains_node(gr_unlabelled_directed, &node1));
    TEST_ASSERT_TRUE(graph_contains_node(gr_unlabelled_directed, &node2));

    TEST_ASSERT_TRUE(graph_add_node(gr_unlabelled_undirected, &node1));
    TEST_ASSERT_TRUE(graph_add_node(gr_unlabelled_undirected, &node2));
    TEST_ASSERT_FALSE(graph_add_node(gr_unlabelled_undirected, &node1));

    TEST_ASSERT_TRUE(graph_contains_node(gr_unlabelled_undirected, &node1));
    TEST_ASSERT_TRUE(graph_contains_node(gr_unlabelled_undirected, &node2));
}

void test_add_and_check_edges(void) {
    int node1 = 1, node2 = 2;

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    TEST_ASSERT_TRUE(graph_add_edge(gr_labelled_directed, &node1, &node2, "label1"));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_labelled_directed, &node1, &node2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr_labelled_directed, &node2, &node1));

    graph_add_node(gr_labelled_undirected, &node1);
    graph_add_node(gr_labelled_undirected, &node2);
    TEST_ASSERT_TRUE(graph_add_edge(gr_labelled_undirected, &node1, &node2, "label1"));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_labelled_undirected, &node1, &node2));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_labelled_undirected, &node2, &node1));

    graph_add_node(gr_unlabelled_directed, &node1);
    graph_add_node(gr_unlabelled_directed, &node2);
    TEST_ASSERT_TRUE(graph_add_edge(gr_unlabelled_directed, &node1, &node2, NULL));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_unlabelled_directed, &node1, &node2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr_unlabelled_directed, &node2, &node1));

    graph_add_node(gr_unlabelled_undirected, &node1);
    graph_add_node(gr_unlabelled_undirected, &node2);
    TEST_ASSERT_TRUE(graph_add_edge(gr_unlabelled_undirected, &node1, &node2, NULL));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_unlabelled_undirected, &node1, &node2));
    TEST_ASSERT_TRUE(graph_contains_edge(gr_unlabelled_undirected, &node2, &node1));
}

void test_remove_edges_and_nodes(void) {
    int node1 = 1, node2 = 2;

    // Grafi diretti ed etichettati
    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "label1");

    TEST_ASSERT_TRUE(graph_remove_edge(gr_labelled_directed, &node1, &node2));
    TEST_ASSERT_FALSE(graph_contains_edge(gr_labelled_directed, &node1, &node2));

    TEST_ASSERT_TRUE(graph_remove_node(gr_labelled_directed, &node1));
    TEST_ASSERT_FALSE(graph_contains_node(gr_labelled_directed, &node1));

}

void test_graph_num_nodes(void) {
    int node1 = 1, node2 = 2;

    TEST_ASSERT_EQUAL(0, graph_num_nodes(gr_labelled_directed));

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);

    TEST_ASSERT_EQUAL(2, graph_num_nodes(gr_labelled_directed));
}

void test_graph_num_edges(void) {
    int node1 = 1, node2 = 2;

    TEST_ASSERT_EQUAL(0, graph_num_edges(gr_labelled_directed));

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "label1");

    TEST_ASSERT_EQUAL(1, graph_num_edges(gr_labelled_directed));
}

void test_graph_get_nodes(void) {
    int node1 = 1, node2 = 2;

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);

    void **nodes = graph_get_nodes(gr_labelled_directed);
    TEST_ASSERT_NOT_NULL(nodes);

    TEST_ASSERT_TRUE((*(int *)nodes[0] == node1) || (*(int *)nodes[1] == node1));
    TEST_ASSERT_TRUE((*(int *)nodes[0] == node2) || (*(int *)nodes[1] == node2));

    free(nodes);
}

void test_graph_get_edges(void) {
    int node1 = 1, node2 = 2, node3 = 3;
    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_node(gr_labelled_directed, &node3);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "edge1");
    graph_add_edge(gr_labelled_directed, &node2, &node3, "edge2");

    Edge **edges = graph_get_edges(gr_labelled_directed);
    TEST_ASSERT_NOT_NULL(edges);
    TEST_ASSERT_EQUAL_INT(*(int *)edges[0]->source, node1);
    TEST_ASSERT_EQUAL_INT(*(int *)edges[0]->dest, node2);
    TEST_ASSERT_EQUAL_STRING(edges[0]->label, "edge1");
    TEST_ASSERT_EQUAL_INT(*(int *)edges[1]->source, node2);
    TEST_ASSERT_EQUAL_INT(*(int *)edges[1]->dest, node3);
    TEST_ASSERT_EQUAL_STRING(edges[1]->label, "edge2");

    for (int i = 0; i < 2; i++) {
        free(edges[i]);
    }
    free(edges);
}

void test_graph_get_neighbours(void) {
    int node1 = 1, node2 = 2, node3 = 3;
    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_node(gr_labelled_directed, &node3);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "edge1");
    graph_add_edge(gr_labelled_directed, &node2, &node3, "edge2");

    void **neighbours = graph_get_neighbours(gr_labelled_directed, &node1);
    TEST_ASSERT_NOT_NULL(neighbours);
    TEST_ASSERT_EQUAL_INT(*(int *)neighbours[0], node2);

    neighbours = graph_get_neighbours(gr_labelled_directed, &node2);
    TEST_ASSERT_NOT_NULL(neighbours);
    TEST_ASSERT_EQUAL_INT(*(int *)neighbours[0], node3);

    free(neighbours);
}

void test_graph_num_neighbours(void) {
    int node1 = 1, node2 = 2;

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "label1");

    TEST_ASSERT_EQUAL(1, graph_num_neighbours(gr_labelled_directed, &node1));
    TEST_ASSERT_EQUAL(0, graph_num_neighbours(gr_labelled_directed, &node2));
}

void test_graph_get_label(void) {
    int node1 = 1, node2 = 2;

    graph_add_node(gr_labelled_directed, &node1);
    graph_add_node(gr_labelled_directed, &node2);
    graph_add_edge(gr_labelled_directed, &node1, &node2, "label1");

    const char *label = graph_get_label(gr_labelled_directed, &node1, &node2);
    TEST_ASSERT_NOT_NULL(label);
    TEST_ASSERT_EQUAL_STRING("label1", label);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_graph_creation);
    RUN_TEST(test_add_and_check_nodes);
    RUN_TEST(test_add_and_check_edges);
    RUN_TEST(test_remove_edges_and_nodes);
    RUN_TEST(test_graph_num_nodes);
    RUN_TEST(test_graph_num_edges);
    RUN_TEST(test_graph_get_nodes);
    RUN_TEST(test_graph_get_edges);
    RUN_TEST(test_graph_get_neighbours);
    RUN_TEST(test_graph_num_neighbours);
    RUN_TEST(test_graph_get_label);


    return UNITY_END();
}

