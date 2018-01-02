#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

void initialize_graph(graph *G , int V) {
    G->total_vertex = V;
    G->adjList = (list*)malloc(sizeof(list)*V);
    for(int i=0; i<V; i++) {
        initializeList(G->adjList[i]);
    }
}

