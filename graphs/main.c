#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

void inputAdjacencyList(graph *G) {
    int V = graph->total_vertex;
    int n; int *ptr;
    // for each vertex
    for(int i=0; i<total_vertex ; i++) {
                
    }
}

int main() {
    char filename[50];
    printf("Taking input from the file: ");
    scanf("%48[^\n]s" , filename);
    
    
    if(freopen(filename,"r",stdin)) {   // redirecting input of the file to the standard input for the convenience
        int V;
        graph G;
        
        scanf(" %d" , &V);
        initializeGraph(&G , V);
        
        clear_graph(&G , V);        
        fclose(stdin);
    }
    return 0;
}