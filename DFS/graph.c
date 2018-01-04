/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	graph.c								*/
/********************************************************/

/* Use Makefile to compile the program. */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

void initialize_graph(graph *G , int V) {
    G->total_vertex = V;
    G->adj_list = (list*)malloc(sizeof(list)*V);
    for(int i=0; i<V; i++) {
        initialize_list(&G->adj_list[i]);
    }
}

/* free the memory allocated to the graph */
void clear_graph(graph *G) {
	for(int i=0; i<G->total_vertex ; i++) {
		clear_list(&G->adj_list[i]);	// clear the adjacent list
	}
	G->total_vertex = 0;				// set the vertex count to zero
	free(G->adj_list);					// free the adjacent list array
}

/* tests whether there is an edge from the vertex x to the vertex y */	
int adjacent(const graph *G, int x, int y) {
	if(0<=x && x<G->total_vertex && 0<=y && y<G->total_vertex && x!=y)
		return contains(&G->adj_list[x] , (COMPARE) compare_int , &y);
	else return 0;
}

/* lists all vertices y such that there is an edge from the vertex x to the vertex y*/
void neighbors(const graph *G, int x) {
	// prints the neighbours of vertex 'x'
	if(0<=x && x<G->total_vertex){
		display_list(&G->adj_list[x] , (DISPLAY)display_int);
		printf("\n");
	}
}

/*adds the edge from the vertex x to the vertex y, if it is not there*/
void add_edge(graph *G, int x, int y){
	// necessary checks for the following function to work bug free
	// self directed edges are not allowed : i.e x != y
	
	if(0<=x && x<G->total_vertex && 0<=y && y<G->total_vertex && x!=y && !adjacent(G , x , y)){
		int *ptr = (int*)malloc(sizeof(int));
		*ptr = y;
		push_back(&G->adj_list[x] , ptr);	
	}
}

/*removes the edge from the vertex x to the vertex y, if it is there*/
void remove_edge(graph *G, int x, int y){
	// necessary checks for the following function to work bug free
	// self directed edges are not allowed : i.e x != y
	if(0<=x && x<G->total_vertex && 0<=y && y<G->total_vertex && x!=y){
		node *nd = get_node(&G->adj_list[x] , (COMPARE)compare_int , &y);
		if(nd!=NULL) remove_node(&G->adj_list[x], nd);	
	}
}

