#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

void input_adjacency_list(graph *G) {
    int n; int *ptr;
    // for each vertex
    for(int i=0; i<G->total_vertex ; i++) {
		// each adjacent list of a vertex is ended by a '-1'
		while(scanf(" %d" , &n) , n!=-1) {
			// printf("%d " , n);
			ptr = (int *)malloc(sizeof(int));
			*ptr = n;
			push_back(&G->adj_list[i] , ptr);	// push the neighbour in the adjacency list of that vertex
		}
    }
}

void display_adj_list(graph *G) {
	for(int i=0; i<G->total_vertex; i++) {
		printf("V:%3d , Adj.List: ", i);
		display_list(&G->adj_list[i] , (DISPLAY)display_int);
		printf("\n");
	}
}

int main() {
    char filename[50];
    printf("Taking input from the file: ");
    scanf("%48[^\n]s" , filename);		// input file
    
    if(freopen(filename,"r",stdin)) {   // redirecting input of the file to the
										// standard input for the convenience
    
	    int V;							// total vertex
        graph G;						// graph declatration	
        
        scanf(" %d" , &V);				// input the total vertex present
        initialize_graph(&G , V);		// initializing the graph
        input_adjacency_list(&G);			// input adjacency list
		
		printf("is there edge from %d to %d : %d\n" ,1 ,2,  adjacent(&G, 1 , 2));
		printf("is there edge from %d to %d : %d\n" ,0 ,2,  adjacent(&G, 0 , 2));
		printf("is there edge from %d to %d : %d\n" ,2 ,4,  adjacent(&G, 2 , 4));
		
		if(G.total_vertex!=0) {
			printf("Adjacency List of the Input Graph: \n");
			display_adj_list(&G);		// prints the adjacent list of the graph
		}
		
        clear_graph(&G);        	// free the memory allocated to the graph
		if(G.total_vertex!=0) {
			printf("Adjacency List of the Input Graph: \n");
			display_adj_list(&G);		// prints the adjacent list of the graph
		}
		
        fclose(stdin);
    }
    return 0;
}