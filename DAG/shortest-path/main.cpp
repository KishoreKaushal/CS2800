#include<iostream>
#include "graph.h"
#include "vector.h"
#include<climits>
#include <iomanip>

#define INF 99999
#define UNDEFINED (-1)

#define TREE_EDGE       (0)
#define FORWARD_EDGE    (1)
#define CROSS_EDGE      (2)
#define BACK_EDGE       (3)


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

/* Printing the Dijkstra Algorithms Results*/
void print_single_source_results(graph &G, int prev[], int dist[], int source){
    int V = G.get_total_vertex();
    cout<<setw(8)<<"Vertex"<<"\t"<<"\tDist\t"<<"Path"<<endl;
    for(int v=0; v<V; ++v) {
        cout<<setw(4)<<v<<"\t\t\t";
        cout<<dist[v]<<"\t";
        /*printing the shortest path from the source*/

        Vector<int> path;
        int curr = v;
        while (curr!=-1) {
            path.push_front(curr);
            curr = prev[curr];
        }
        cout<<path<<endl;
    }
}


/*  recursive implementation of the DFS: assuming the graph is directed acyclic */
void DFS(graph &G , int V , Vector<bool> &discovered , Vector<int> &ts) {
	int W;
	discovered[V] = true;
    for(auto itr = G.adj_list[V].begin() ; itr!=G.adj_list[V].end() ; ++itr) {
        W = (*itr).node_num;
        if(discovered[W] == false) {
            G.pi[W] = V;
            DFS(G , W , discovered , ts);
        }
    }
    ts.push_front(V);    // topological sorting
}

void dag_shortest_path(graph &G , int source , int dist[] , int prev[]) {
    Vector <bool> discovered(V , false);
    Vector <int> ts;        // topological sort: most prior element in front
    int V = G.get_total_vertex();
    int v , wt;

    /*Topological Sort*/
    for(int i=0; i<V; ++i) {
        if(!discovered[i]) {
            DFS(G , i, discovered , ts);
        }
    }

    /* Initialization*/
    for(int i=0; i<V; ++i) {
        dist[i] = INF;
        prev[i] = UNDEFINED;
    }
    dist[source] = 0;

    /*for each vertex taken in topological sorted order*/
    for(auto itr_int = ts.begin() ; itr_int!=ts.end() ; ++itr_int){
        u = *itr_int;
        /*Relax each edge*/
        for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
            v = (*itr).node_num;
            wt = (*itr).weight;
            if(dist[u]+wt < dist[v]) {
                dist[v] = dist[u]+wt;
                prev[v] = u;
            }
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
        scanf(" %d" , &V);				// input the total vertex present
        graph G(V);						// graph declaration

        input_data(G);                  // input the graph

        G.print();                      // print the graph

        int *dist = new int[V];
        int *prev = new int[V];

        int source=0;    // source vertex
        cout<<endl;
        cin>>source;
        // for (int source=0; source<V; ++source) {
            cout<<"Source Vertex: "<<source<<endl;
            dag_shortest_path(G, source, dist, prev);
            print_single_source_results(G, prev, dist, source);
            cout<<endl;
        // }

        delete dist;
        delete prev;
        fclose(stdin);
    }
    return 0;
}
