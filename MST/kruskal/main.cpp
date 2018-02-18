/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	main.cpp      						*/
/*	Objective	:	Kruskal Algorithm           		*/
/********************************************************/

/* Undirected graph */

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include "vector.h" // vector implementation
#include "graph.h"  // graph implementation
#include "union_find.h" // union-find data structure

#define MAXSIZE (200)
#define INF (INT_MAX)
#define UNDEFINED (-1)

using namespace std;

void merge(edge_list &E , int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    edge_list L(n1+1);
    edge_list R(n2+1);
    for (int i=0; i<n1; ++i) { L.e[i] = E.e[p+i];}
    for (int i=0; i<n2; ++i) { R.e[i] = E.e[q+i+1];}
    L.e[n1] = edge(INF);
    R.e[n2] = edge(INF);
    int i=0;
    int j=0;
    for (int k=p; k<=r; ++k) {
        if(L.e[i]<=R.e[j]) {
            E.e[k] = L.e[i];
            ++i;
        } else {
            E.e[k] = R.e[j];
            ++j;
        }
    }
}

void merge_sort(edge_list &E , int p, int r) {
    if(p<r) {
        int q = (p+r)/2;
        merge_sort(E, p,q);
        merge_sort(E, q+1, r);
        merge(E , p, q, r);
    }
}

void sort_edge_list(edge_list &E) {
    // using merge sort to do it
    merge_sort(E, 0, E.num_edges-1);
}

void kruskal(graph &G, int source, edge_list &E) {
    union_find u(G.get_total_vertex());  // intialization step
    sort_edge_list(E);
    G.mst.clear();
    edge e;
    for (int i=0; i<E.num_edges ; ++i) {
        e = E.e[i];
        // if FIND-SET(u) != FIND-SET(v)
        if(!u.is_same_set(e.u, e.v)){
            G.mst.push_back(e);
            u.union_set(e.u, e.v);
        }
    }
}

// wrapper function for calling the prims algorithm
void print_mst(graph &G , int source, edge_list &E) {
    kruskal(G, source, E);
    int total_weight = 0;
    cout<<"\033[1;31mMST-KRUSKAL \033[0m{"<<endl;
    for(Vector<edge>::iterator itr = G.mst.begin(); itr!=G.mst.end(); ++itr) {
        cout<<"\t{ \033[1;32m("<<(*itr).u<<" , "<<(*itr).v<<")\033[0m : \033[1;33m "<<(*itr).wt<<"\033[0m } ,"<<endl;
        total_weight+=(*itr).wt;
    }
    cout<<"}"<<endl;
    cout<<"Total Weight: "<<total_weight<<endl;
}

void input_data(graph &G , edge_list &E) {
    for(int i=0; i<E.num_edges ; ++i) {
        cin>>E.e[i].u>>E.e[i].v>>E.e[i].wt;
        G.add_edge(E.e[i].u, E.e[i].v, E.e[i].wt);
        G.add_edge(E.e[i].v, E.e[i].u, E.e[i].wt);
    }
}

int main() {
    char filename[50];
    printf("Taking input from the file: ");
    scanf("%48[^\n]s" , filename);		// input file

    if(freopen(filename,"r",stdin)) {   // redirecting input of the file to the
										// standard input for the convenience

	    int num_V, num_E;							// total vertex and total edges
        cin>>num_V;				// input the total vertex present
        cin>>num_E;
        edge_list E(num_E);
        graph G(num_V);						// graph declaration

        input_data(G, E);                  // input the graph

        G.print();                      // print the graph
        sort_edge_list(E);              // sort the edge list
        cout<<"\nSorted list: "<<endl<<E<<endl;
        int source=0;    // source vertex
        cout<<endl;
        cin>>source;
        print_mst(G , source, E);
        fclose(stdin);
    }
    return 0;
}
