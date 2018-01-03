#include<stdio.h>
#include<stdlib.h>
#include "list.h"

#ifndef GRAPH_H
#define GRAPH_H

void display_int(int *ptr);
int compare_int(int *a , int *b);

typedef struct graph {
    int total_vertex;
    list *adj_list;
} graph ;

/* initializes the graph */
void initialize_graph(graph *G , int V);

/* tests whether there is an edge from the vertex x to the vertex y */
int adjacent(const graph *G, int x, int y);

/* lists all vertices y such that there is an edge from the vertex x to the vertex y*/
void neighbors(const graph *G, int x);

///*adds the vertex x, if it is not there*/
//void add_vertex(graph *G, int x);
//
///*removes the vertex x, if it is there*/
//void remove_vertex(graph *G, int x);

/*adds the edge from the vertex x to the vertex y, if it is not there*/
void add_edge(graph *G, int x, int y);

/*removes the edge from the vertex x to the vertex y, if it is there*/
void remove_edge(graph *G, int x, int y);

void clear_graph(graph *G);

#endif // GRAPH_H