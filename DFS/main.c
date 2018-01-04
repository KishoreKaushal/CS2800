/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	main.c 								*/
/*	Objective	:	Classification of the edges in 		*/
/*					a DFS-tree traversal 				*/
/********************************************************/

/* Use Makefile to compile the program. */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"
#include "graph.h"

#define NOT_DISCOVERED 	(0)
#define DISCOVERED 		(1)


/* accepts adjacency list of a graph as input */
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
void DFS_recursive(graph *G , int V , int *discovered , int *previsit , int *postvisit ,
		int *clock, int *traversal, int *idx) {
    
	int W;
	printf("%d ", V);
	// insert the V in the tree-traversal path
	traversal[*idx] = V;
	(*idx)++;
	previsit[V] = *clock;
	(*clock)++;
	
	discovered[V] = DISCOVERED;
    node *nd = G->adj_list[V].front;
    while(nd!=NULL) {
        W = *(int*)(nd->data);
        if(discovered[W]==NOT_DISCOVERED) {
            DFS_recursive(G , W , discovered , previsit , postvisit , clock, traversal, idx);
        }
        nd = nd->next;
    }
	postvisit[V] = *clock;
	(*clock)++;
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

void display_edge_classification(graph *G, int *previsit , int *postvisit, int *traversal) {
	node *itr_nd;
	int u, v;
	// iterate through all the edges using the adjacency list
	// directed edge from u to v is represented as : (u , v) or (u --> v)
	for(u=0; u<G->total_vertex; u++) {
		itr_nd = G->adj_list[u].front;
		while(itr_nd!=NULL) {
			v = *(int*)(itr_nd->data);
			if(previsit[u]!=-1 && previsit[v]!=-1) {
				if(previsit[u] <= previsit[v] && postvisit[v]<= postvisit[u] ) {
					// case of Tree/Forward edge
					int idx=-1;
					for (int i=0 ; i<G->total_vertex && traversal[i]!=-1; i++) {
						if(traversal[i]==v) {
							idx = i;
							break;
						}
					}
					
					for (int i=idx-1 ; i>=0; i++) {
						if(contains_int(&G->adj_list[traversal[i]] , v)) {
							// first traversal[i] having an edge to v :
							// then this is the parent vertex of v in the DFS tree
							if(traversal[i]==u) {
								// u is the parent node of v in DFS tree
								// which confirms that (u --> v) is a tree edge
								// set idx = -1
								idx = -1;
							}
							break;
						}
					}
					
					// if idx is -1 : (u --> v) is a tree edge
					if(idx==-1) printf("(%3d --> %3d) : TREE EDGE\n" , u , v);
					else printf("(%3d --> %3d) : FORWARD EDGE\n" , u , v);
				
				} else if(previsit[v] <= previsit[u] && postvisit[u] <= postvisit[v]) {
					// case of back edge
					printf("(%3d --> %3d) : BACK EDGE\n" , u , v);
				} else if(postvisit[v] <= previsit[u]) {
					// case of cross edge
					printf("(%3d --> %3d) : CROSS EDGE\n" , u , v);
				}
			}
			itr_nd = itr_nd->next;
		}
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
		display_adj_list(&G);			// display adjacency list of the graph
		
		printf("\n");
		printf("DFS-iterative: ");		
		DFS_iterative(&G , 0);			// Depth-first-search using stack based implementation
		printf("\n");
		
        printf("DFS-Recursive: ");
        int *discovered = (int *)malloc(sizeof(int)*G.total_vertex);
		int *previsit = (int *)malloc(sizeof(int)*G.total_vertex);
		int *postvisit = (int *)malloc(sizeof(int)*G.total_vertex);
		int *traversal = (int *)malloc(sizeof(int)*G.total_vertex);
		int clock = 0, idx=0;
		
        for(int i=0; i<G.total_vertex; i++){
			traversal[i] = postvisit[i] = previsit[i] = discovered[i] = NOT_DISCOVERED;
		}
		
		DFS_recursive(&G , 0 , discovered, previsit , postvisit , &clock, traversal , &idx);
		printf("\n");
		printf("\n");
		/*classification of all the edges can be done using the information in previsit and postvist */
		display_edge_classification(&G, previsit , postvisit, traversal);
		
		/* free the memory allocated to the graph and arrays */
		clear_graph(&G);
        free(discovered);
		free(previsit);
		free(postvisit);
		free(traversal);
		/* close the link of the file stream to the stdin */
        fclose(stdin);
    }
    return 0;
}