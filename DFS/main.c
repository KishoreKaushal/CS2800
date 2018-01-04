#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"
#include "graph.h"

#define NOT_DISCOVERED (0)
#define DISCOVERED (1)

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

/*  recursive implementation of the DFS */
void DFS_recursive(graph *G , int V , int *discovered) {
    int W;
    if(discovered[V]==NOT_DISCOVERED) printf("%d ", V);
	discovered[V] = DISCOVERED;
    node *nd = G->adj_list[V].front;
    while(nd!=NULL) {
        W = *(int*)(nd->data);
        if(discovered[W]==NOT_DISCOVERED) {
            DFS_recursive(G , W , discovered);
        }
        nd = nd->next;
    }
}

/* iterative stack implementation of the DFS */
void DFS_iterative(graph *G , int V) {
    // V : starting vertex
    int *discovered = (int *)malloc(sizeof(int)*G->total_vertex);
    for(int i=0; i<G->total_vertex; i++) discovered[i] = NOT_DISCOVERED;
    
    int W;
    stack stk;
    initialize_stack(&stk);
    push_int(&stk , V);
    
    while(!stack_empty(&stk)) {
        V = pop_int(&stk);
        //printf("V: %d\n" , V);
        if(discovered[V] == NOT_DISCOVERED) {
            discovered[V] = DISCOVERED;
            printf("%d " , V);
            // for all edges from vertex V to W
            node *nd = G->adj_list[V].front;
            while(nd!=NULL) {
                W = *(int*)(nd->data);
                push_int(&stk , W);
                nd = nd->next;
            }
        }
    }
    clear_stack(&stk);
    free(discovered);
}

void display_adj_list(graph *G) {
	for(int i=0; i<G->total_vertex; i++) {
		printf("V:%3d , Adj.List: ", i);
		display_list(&G->adj_list[i] , (DISPLAY)display_int);
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
        input_adjacency_list(&G);		// input adjacency list
		display_adj_list(&G);
		printf("DFS-iterative: ");
		DFS_iterative(&G , 0);
		printf("\n");
        printf("DFS-Recursive: ");
        int *discovered = (int *)malloc(sizeof(int)*G.total_vertex);
        for(int i=0; i<G.total_vertex; i++) discovered[i] = NOT_DISCOVERED;
		DFS_recursive(&G , 0 , discovered);
        printf("\n");
        clear_graph(&G);        	    // free the memory allocated to the graph
        free(discovered);
        fclose(stdin);
    }
    return 0;
}