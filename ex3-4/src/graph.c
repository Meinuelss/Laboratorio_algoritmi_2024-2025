#include <stdlib.h>
#include "graph.h"
#include "hash_table.h"
#include "bfs.h"

typedef struct graph{
	int labelled;
	int directed;
	HashTable *nodes;
	int num_edges;
} *Graph;

Graph graph_create(int labelled, int directed, int (*compare)(const void *, const void *), unsigned long (*hash)(const void *)){
	Graph gr = malloc(sizeof(*gr));
	if (!gr) return NULL;
	
	gr->labelled = labelled;
	gr->directed = directed;
	gr->nodes = hash_table_create(compare, hash);
	if (!gr->nodes){
		free(gr);
		return NULL;
	}
	gr->num_edges = 0;
	return gr;
}

int graph_is_directed(const Graph gr){
	if (!gr) return 0;

	return gr->directed;
}

int graph_is_labelled(const Graph gr){
	if (!gr) return 0;

	return gr->labelled;
}

int graph_add_node(Graph gr, const void *node){
	if (!gr || !node) return 0;

	
	if (hash_table_contains_key(gr->nodes, node)){
		return 0;
	}

	HashTable *edges = hash_table_create(gr->nodes->cmp, gr->nodes->hash);
	if (!edges){
		return -1;
	}

	hash_table_put(gr->nodes, node, edges);
	return 1;
}

int graph_contains_edge(const Graph gr, const void *node1, const void *node2) {
	if (!gr || !node1 || !node2) return 0;

	if (!hash_table_contains_key(gr->nodes, node1)) return 0;

	HashTable *list_adjacency = hash_table_get(gr->nodes, node1);
	return hash_table_contains_key(list_adjacency, node2);
}

int graph_contains_node(const Graph gr, const void *node){
	if (!gr || !node) return 0;

	return hash_table_contains_key(gr->nodes, node);
}
	
int graph_remove_node(Graph gr, const void *node){
	if (!gr || !node) return 0;

	if (!hash_table_contains_key(gr->nodes, node)){
		return 0;
	}

	HashTable *list_adjacency = hash_table_get(gr->nodes, node);
	if (list_adjacency){
		void **neighbours = hash_table_keyset(list_adjacency);
		if (neighbours){
			for (int i = 0; i < hash_table_size(list_adjacency); i++){
				graph_remove_edge(gr, node, neighbours[i]);
			}
			free(neighbours);
		}
		hash_table_free(list_adjacency);
	}

	void **nodes = hash_table_keyset(gr->nodes);
	if (!nodes){
		printf("Errore: Impossibile ottenere le chiavi del grafo.\n");
		return 0;
	}
	for (int i = 0; i < hash_table_size(gr->nodes); i++){
		HashTable *list_adjacency2 = hash_table_get(gr->nodes, nodes[i]);
		if(!list_adjacency2){
			continue;
		}
	}
	hash_table_remove(gr->nodes, node);
	return 1;
}

int graph_add_edge(Graph gr, const void *node1, const void *node2, const void *label){
	if (!gr || !node1 || !node2) return 0;

	if (!hash_table_contains_key(gr->nodes, node1) || !hash_table_contains_key(gr->nodes, node2)) return 0;

	HashTable *list_adjacency = hash_table_get(gr->nodes, node1);

	if (!list_adjacency) return 0;

	if (hash_table_contains_key(list_adjacency, node2)){
		return 0;
	}

	hash_table_put(list_adjacency, strdup(node2), (void *)label);
	gr->num_edges++;

	if (!gr->directed){
		HashTable *reverse_list_adjacency = hash_table_get(gr->nodes, node2);
		if (reverse_list_adjacency){
			hash_table_put(reverse_list_adjacency, strdup(node1), (void *)label);
		}
	}
	return 1;
}

int graph_remove_edge(Graph gr, const void *node1, const void *node2){
	if (!gr || !node1 || !node2) return 0;

	if (!hash_table_contains_key(gr->nodes, node1)) {
		return 0;
	}

	HashTable *list_adjacency = hash_table_get(gr->nodes, node1);
	if (!list_adjacency || !hash_table_contains_key(list_adjacency, node2)){
		return 0;
	}

	hash_table_remove(list_adjacency, node2);
	gr->num_edges--;
	
	if (!gr->directed){
		if (hash_table_contains_key(gr->nodes, node2)){
			HashTable *reverse_list_adjacency = hash_table_get(gr->nodes, node2);
			if (hash_table_contains_key(reverse_list_adjacency, node1)){
				hash_table_remove(reverse_list_adjacency, node1);
			}
		}
	}

	return 1;
}

int graph_num_nodes(const Graph gr){
	if (!gr) return 0;
	
	return hash_table_size(gr->nodes);
}

int graph_num_edges(const Graph gr){
	if (!gr) return 0;
	
	return gr->num_edges;
}

void **graph_get_nodes(const Graph gr){
	if (!gr) return NULL;
    
	return hash_table_keyset(gr->nodes);
}

Edge** graph_get_edges(const Graph gr){						
	if (!gr || gr->num_edges<=0) return NULL;

	Edge **edges = malloc((size_t)gr->num_edges * sizeof(Edge *));
	if (!edges) return NULL;

	int idx = 0;
	void **nodes = hash_table_keyset(gr->nodes);
	if (!nodes) return NULL;
		
	for (int i = 0; i < hash_table_size(gr->nodes); i++){
		HashTable *list_adjacency = hash_table_get(gr->nodes, nodes[i]);
		if (!list_adjacency) 
			continue;

		void **neighbours = hash_table_keyset(list_adjacency);
		if (neighbours){
			for (int j = 0; j < hash_table_size(list_adjacency); j++){
				Edge *edge = malloc(sizeof(*edge));
				if (!edge){
					return NULL;
				}
				edge->source = nodes[i];
				edge->dest = neighbours[j];
				edge->label = hash_table_get(list_adjacency, neighbours[j]);
				edges[idx++] = edge;
			}
			free(neighbours);
		}
	}
	free(nodes);
	return edges;
}

void** graph_get_neighbours(const Graph gr, const void* node){
	if (!gr || !node || !graph_contains_node(gr, node)){
		printf("Errore: Nodo non valido o non trovato.\n");
		return NULL;
	}

	HashTable* adjacency_list = hash_table_get(gr->nodes, node);
	if (!adjacency_list){
		return NULL;
	}

	void** neighbours = hash_table_keyset(adjacency_list);
    return neighbours;
}

int graph_num_neighbours(const Graph gr, const void *node){
	if (!gr || !node) return 0;
	
	if (!hash_table_contains_key(gr->nodes, node)) return 0;

	HashTable *list_adjacency = hash_table_get(gr->nodes, node);
	if (!list_adjacency) return 0;
	
	return hash_table_size(list_adjacency);
}

void *graph_get_label(const Graph gr, const void *node1, const void *node2){
	if (!gr || !node1 || !node2) return NULL;

	if (!hash_table_contains_key(gr->nodes, node1)) return NULL;
	
	HashTable *list_adjacency = hash_table_get(gr->nodes, node1);
	if (!list_adjacency) return NULL;

	return hash_table_get(list_adjacency, node2);
}

void graph_free(Graph gr){
	if (!gr) return;

	void **nodes = hash_table_keyset(gr->nodes);
	if (nodes){
		for (int i = 0; i < hash_table_size(gr->nodes); i++){
			HashTable *list_adjacency = hash_table_get(gr->nodes, nodes[i]);
			if (list_adjacency){
                hash_table_free(list_adjacency);
			}
		}
		free(nodes);
	}

	hash_table_free(gr->nodes);
	free(gr);
}
