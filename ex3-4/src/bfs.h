#ifndef BFS_H
#define BFS_H

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/**
 * @brief Duplicates a string, allocating memory dynamically.
 * This function creates a copy of the given string by allocating a new memory block
 * and copying the contents of the original string into it.
 * 
 * @param str: The original string to duplicate.
 * @return Returns a pointer to the newly duplicated string, or NULL if memory allocation fails.
 */
char* strdup(const char* str);

/**
 * @brief Reads a CSV file and builds a graph from its contents.
 * 
 * @param file: A pointer to the input file to read.
 * @param gr: A pointer to the graph to populate with nodes and edges.
 * @return Returns 1 if the graph is successfully built, 0 if an error occurs (e.g., file format issues).
 */
void read_csv_and_build_graph(FILE *file, Graph gr);

/**
 * @brief This function starts at a given node and explores the graph step by step.
 * It visits all the nodes that can be reached from the starting node, 
 * one layer at a time (visits by breadth). The nodes closer to the starting point are visited first.
 * 
 * @param gr: The graph to traverse.
 * @param start: The starting node for the BFS traversal.
 * @param compare: A function to compare nodes during the traversal.
 * @param hash: A function to calculate the hash for nodes.
 * @return Returns an array of nodes in the order they were visited, or NULL if the starting node does not exist.
 */
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

/**
 * @brief Writes the result of a BFS to a file.
 * 
 * @param file: A pointer to the output file.
 * @param bfs_result: An array of nodes visited during the BFS traversal.
 * @return Returns 1 if the operation succeeds, 0 otherwise.
 */
int write_bfs_result_to_file(FILE *file, void** bfs_result);

#endif // BFS_H
