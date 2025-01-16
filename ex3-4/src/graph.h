#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph *Graph;

typedef struct edge 
	{
    void* source;
	void* dest;
	void* label;
	} Edge;

/**
 * @brief Creates an empty graph with customizable properties.
 * 
 * @param labelled: 1 if the graph supports labels on edges, 0 otherwise.
 * @param directed: 1 if the graph is directed (edges have directions), 0 otherwise.
 * @param compare: A function to compare two nodes.
 * @param hash: A function to compute the hash of a node.
 * @return Returns the newly created graph structure.
 */
Graph graph_create(int labelled, int directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

/**
 * @brief Checks if the graph is directed. A directed graph has edges 
 * es: A->B and non-directed has edges es: A<->B
 * 
 * @param gr: The graph to check.
 * @return Returns 1 if the graph is directed, 0 otherwise.
 */
int graph_is_directed(const Graph gr);

/**
 * @brief Checks if the graph has labels on each edge.
 * 
 * @return Returns 1 if the graph supports labels, 0 otherwise.
 */
int graph_is_labelled(const Graph gr);

/**
 * @brief Adds a new node to the graph. If it already exists, the function does nothing.
 * 
 * @param node: The node to insert into the graph.
 * @return Returns 1 if the node is added successfully, 0 if the node already exists.
 */
int graph_add_node(Graph gr, const void* node);

/**
 * @brief Adds an edge between two nodes in the graph. 
 * Connects two existing nodes in the graph with an edge. 
 * If the graph is directed, the edge goes from `node1` to `node2`. 
 * If the graph is not directed, the edge is bidirectional.
 * 
 * @param node1: The source node of the edge.
 * @param node2: The destination node of the edge.
 * @param label: The label for the edge (NULL if is non-labelled).
 * @return Returns 1 if the edge is added successfully, 0 otherwise.
 */
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label);

/**
 * @brief Checks if a node exists in the graph.
 *
 * @param node: The node to search for.
 * @return Returns 1 if the node is present, 0 otherwise.
 */
int graph_contains_node(const Graph gr, const void* node);

/**
 * @brief Checks if an edge exists between two nodes.
 * 
 * @param node1: The source node.
 * @param node2: The destination node.
 * @return Returns 1 if the edge exists, 0 otherwise.
 */
int graph_contains_edge(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Removes a node from the graph.
 * 
 * @param node: The node to remove.
 * @return Returns 1 if the node is removed successfully, 0 otherwise.
 */
int graph_remove_node(Graph gr, const void* node);

/**
 * @brief Removes an edge between two nodes.
 * Deletes an edge between `node1` and `node2`. For directed graphs, the edge
 * must go from `node1` to `node2`. For undirected graphs, the connection
 * is removed in both directions.
 * 
 * @param node1: The source node.
 * @param node2: The destination node.
 * @return Returns 1 if the edge is removed successfully, 0 otherwise.
 */
int graph_remove_edge(Graph gr, const void* node1, const void* node2);

/**
 * @brief Counts the number of nodes in the graph.
 * 
 * @return Returns the total number of nodes in the graph.
 */
int graph_num_nodes(const Graph gr);

/**
 * @brief Counts the number of edges in the graph.
 * 
 * @return Returns the total number of edges in the graph.
 */
int graph_num_edges(const Graph gr);

/**
 * @brief Creates and returns an array containing all nodes in the graph.
 * 
 * @return Returns an array of pointers to all nodes in the graph.
 */
void** graph_get_nodes(const Graph gr);

/**
 * @brief Creates and returns an array containing all edges 
 * the graph (Each edge is represented as an 'Edge' structure).
 * 
 * @return Returns an array of pointers to all edges in the graph.
 */
Edge** graph_get_edges(const Graph gr);

/**
 * @brief Finds and returns all nodes that are directly connected to a given node.
 * 
 * @param node: The node whose neighbors will be return.
 * @return Returns an array of pointers to all neighboring nodes.
 */
void** graph_get_neighbours(const Graph gr, const void* node);

/**
 * @brief Counts the number of neighbors of a node.
 * 
 * @param node: The node whose neighbors will be counted.
 * @return Returns the total number of neighbors.
 */
int graph_num_neighbours(const Graph gr, const void* node);

/**
 * @brief Finds and returns the label associated with an edge between two nodes.
 * 
 * @param node1: The source node of the edge.
 * @param node2: The destination node of the edge.
 * @return Returns the label of the edge, or NULL if no edge exists or the graph is not labelled.
 */
void* graph_get_label(const Graph gr, const void* node1, const void* node2);

/**
 * @brief Deallocates all memory associated with the graph, including nodes, edges,
 * and internal structures.
 * 
 */
void graph_free(Graph gr);

#endif // GRAPH_H
