#include<iostream>
#include "graph.h"
#include "vector.h"
#include<climits>
#include <iomanip>

#define INF 99999
#define UNDEFINED (-1)

using namespace std;

bool bellman_ford(graph &G , int source ,  int dist[], int prev[]) {
    bool updates = false;
    int V = G.get_total_vertex();
    int v , wt;
    /* Initialization*/
    for(int i=0; i<V; ++i) {
        dist[i] = INF;
        prev[i] = UNDEFINED;
    }
    dist[source] = 0;
    // cout<<"Line: "<<__LINE__<<endl;
    for(int i=1; i<V ; ++i) {
        updates = false;
        /* Relax each edge */
        for(int u=0; u<V; ++u) {
            for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
                v = (*itr).node_num;
                wt = (*itr).weight;
                if(dist[u]+wt < dist[v]) {
                    dist[v] = dist[u]+wt;
                    prev[v] = u;
                    updates = true;
                }
            }
        }
        if(updates == false ) break;
    }
    // cout<<"Line: "<<__LINE__<<endl;
    for(int u=0; u<V; ++u) {
        for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
            v = (*itr).node_num;
            wt = (*itr).weight;
            if(dist[u]+wt < dist[v]) {
                /* Negative Cycle Reachable from Source */
                return false;
            }
        }
    }
    // cout<<"Line: "<<__LINE__<<endl;
    return true;
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


int main() {
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
            if(bellman_ford(G, source, dist, prev)){
                print_single_source_results(G, prev, dist, source);
            } else cout<<"Negative Weighted Cycle Detected."<<endl;
            cout<<endl;
        // }

        delete dist;
        delete prev;
    return 0;
}
