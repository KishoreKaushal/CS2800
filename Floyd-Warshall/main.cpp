#include<iostream>
#include "graph.h"
#include "vector.h"
#include<climits>
#include <iomanip>

#define INF 99999
#define UNDEFINED (-1)

using namespace std;

void floyd_warshall(graph &G , int **dist){
    int V = G.get_total_vertex();
    int v, wt;
    /*Initialization*/
    for(int i=0; i<V; ++i) {
        for(int j=0; j<V; ++j){
            dist[i][j] = INF;
        }
    }
    for(int i=0; i<V; ++i) dist[i][i] = 0;
    /* for each edge  (u-->v) */
    for(int u=0; u<V; ++u) {
        for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
            v = (*itr).node_num;
            wt = (*itr).weight;
            dist[u][v] = wt;
        }
    }

    /*------------Operation Starts Here --------------*/
    for (int k=0 ; k<V ; ++k) {
        for(int i=0; i<V; ++i) {
            for (int j=0; j<V; ++j) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

/* A utility function to print solution */
void print_dist2D(int **dist, int V){
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void input_data(graph &G) {
    int E;  // total edges
    int u , v , wt;  // u --wt-- v : an edge
    cin>>E;
    for(int i=0; i<E ; ++i) {
        cin>>u>>v>>wt;
        G.add_edge(u, v, wt);
        G.add_edge(v, u, wt);
    }
}



int main() {
    char filename[50];
    printf("Taking input from the file: ");
    scanf("%48[^\n]s" , filename);		// input file

    if(freopen(filename,"r",stdin)) {   // redirecting input of the file to the
										// standard input for the convenience

	    int V;							// total vertex
        scanf(" %d" , &V);				// input the total vertex present
        graph G(V);						// graph declaration

        input_data(G);                  // input the graph

        G.print();                      // print the graph
        int** dist2D = new int*[V];
        for(int i = 0; i < V; ++i)  dist2D[i] = new int[V];

        floyd_warshall(G , dist2D);
        print_dist2D(dist2D, V);
        for(int i = 0; i < V; ++i) {
            delete [] dist2D[i];
        }
        delete [] dist2D;
        fclose(stdin);
    }
    return 0;
}
