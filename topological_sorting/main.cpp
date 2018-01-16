#include<iostream>
#include <stdio.h>
#include <stdlib.h>
// #include "list.h"
#include "graph.h"

using namespace std;

void input_adj_list(graph &G) {
    int n;  // input int
    // for each vertex
    for(int i=0; i<G.get_total_vertex() ; i++) {
		// each adjacent list of a vertex is ended by a '-1'
		while(cin>>n , n!=-1) {
			// printf("%d " , n);
			G.add_edge(i, n);
		}
    }
}

/*  recursive implementation of the DFS */
void DFS_recursive(graph &G , int V , Vector<bool> &discovered , Vector<int> &ts) {
	int W;
	discovered[V] = true;
    for(auto itr = G.adj_list[V].begin() ; itr!=G.adj_list[V].end() ; ++itr) {
        W = (*itr).node_num;
        if(discovered[W] == false) {
            DFS_recursive(G , W , discovered , ts);
        }
    }
    ts.push_front(V);    // topological sorting
}

int main() {
    char filename[50];
    printf("Taking input from the file: ");
    scanf("%48[^\n]s" , filename);		// input file

    if(freopen(filename,"r",stdin)) {   // redirecting input of the file to the
										// standard input for the convenience

	    int V;							// total vertex
        scanf(" %d" , &V);				// input the total vertex present

        graph G(V);						// graph declatration

        input_adj_list(G);			// input adjacency list

		// printf("is there edge from %d to %d : %d\n" ,1 ,2,  G.adjacent(1 , 2));
		// printf("is there edge from %d to %d : %d\n" ,0 ,2,  G.adjacent(0 , 2));
		// printf("is there edge from %d to %d : %d\n" ,2 ,4,  G.adjacent(2 , 4));
        //
        // cout<<endl;
        //
		// if(!G.empty()) {
		// 	printf("Adjacency List of the Input Graph: \n");
		// 	G.print();		// prints the adjacent list of the graph
		// 	cout<<endl;
		// }
        //
		// int x=0 , y=0, s;
        //
		// while(s=scanf(" %d %d" , &x , &y) , (s!=EOF)&&(x||y)) {
		// 	printf("Removing edge between the vertex %d and %d\n" , x , y);
		// 	G.remove_edge(x , y);
		// }
        //
        // cout<<endl;
        //
		// if(!G.empty()) {
		// 	printf("Adjacency List of the Input Graph: \n");
		// 	G.print();		// prints the adjacent list of the graph
		// 	cout<<endl;
		// }
        //
        // G.clear();      	// free the memory allocated to the graph
		// if(!G.empty()) {
		// 	printf("Adjacency List of the Input Graph: \n");
		// 	G.print();		// prints the adjacent list of the graph
		// 	cout<<endl;
		// }

        Vector <bool> discovered(V , false);
        Vector <int> ts;    // topological sort

        // DFS : forest of trees
        for(int i=0; i<V; ++i) {
            if(!discovered[i]) {
                DFS_recursive(G , i, discovered , ts);
            }
        }

        cout<<"Topological Sorting: "<<ts<<endl;
        fclose(stdin);
    }
    return 0;
}
