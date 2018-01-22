#include<iostream>
#include <stdio.h>
#include <stdlib.h>
// #include "list.h"
#include "graph.h"

#define TREE_EDGE       (0)
#define FORWARD_EDGE    (1)
#define CROSS_EDGE      (2)
#define BACK_EDGE       (3)

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
void DFS_recursive(graph &G , int V , Vector<bool> &discovered , Vector<int> &ts , Vector<int> &traversal) {
	int W;
	discovered[V] = true;
    G.previsit[V] = G.clock++;
    traversal.push_back(V);

    for(auto itr = G.adj_list[V].begin() ; itr!=G.adj_list[V].end() ; ++itr) {
        W = (*itr).node_num;
        if(discovered[W] == false) {
            G.pi[W] = V;
            DFS_recursive(G , W , discovered , ts, traversal);
        }
    }
    G.postvisit[V] = G.clock++;
    ts.push_front(V);    // topological sorting
}

int classify_edge(graph &G, Vector<int> &traversal , int u, int v) {
    if(G.previsit[u]!=0 || G.previsit[v]!= 0) {
        if(G.previsit[u] <= G.previsit[v] && G.postvisit[v]<= G.postvisit[u] ) {
            // tree/forward edge
            int idx=-1, i;
            Vector<int>::iterator itr=traversal.begin();
            for(int i=0 ; itr!=traversal.end() && i<G.total_vertex; ++i, ++itr) {
                if(*itr == v) {
                    idx = i;
                    break;
                }
            }
            --itr;
			for (int i=idx-1 ; i>=0 && itr!=traversal.rend(); i-- , --itr) {
                //printf("%d %d\n", __LINE__ , traversal[i]);
                if(G.adjacent(*itr , v)) {
				// if(contains_int(&G->adj_list[traversal[i]] , v)) {
					// first traversal[i](=*itr) having an edge to v :
					// then this is the parent vertex of v in the DFS tree
					if(*itr==u) {
						// u is the parent node of v in DFS tree
						// which confirms that (u --> v) is a tree edge
						// set idx = -1
						idx = -1;
					}
					break;
				}
			}
			// if idx is -1 : (u --> v) is a tree edge
			if(idx==-1) return TREE_EDGE;
			else return FORWARD_EDGE ;
        } else if(G.previsit[v] <= G.previsit[u] && G.postvisit[u] <= G.postvisit[v]) {
            // back edge
            return BACK_EDGE;
        } else if (G.postvisit[v] <= G.previsit[u]) {
            // cross edge
            return CROSS_EDGE;
        }
    }
    return -1;
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
        Vector <int> traversal;

        // DFS : forest of trees
        bool back_edge_present = false;
        for(int i=0; i<V; ++i) {
            if(!discovered[i]) {
                G.reset_previsit_postvisit();
                cout<<"Root Node: "<<i<<endl;
                DFS_recursive(G , i, discovered , ts , traversal);
                Vector<int>::iterator itr1 , itr2;
                for(itr1 = traversal.begin() ; itr1!=traversal.end() ; ++itr1) {
                    for(itr2 = traversal.begin() ; itr2!=traversal.end(); ++itr2) {
                        if(G.adjacent(*itr1 , *itr2)) {
                            switch (classify_edge(G,traversal , *itr1, *itr2)) {
                                case BACK_EDGE: cout<<"("<<*itr1<<"->"<<*itr2<<") : BACK_EDGE"<<endl;
                                back_edge_present=true;
                                break;
                                case TREE_EDGE: cout<<"("<<*itr1<<"->"<<*itr2<<") : TREE_EDGE"<<endl;
                                break;
                                case FORWARD_EDGE: cout<<"("<<*itr1<<"->"<<*itr2<<") : FORWARD_EDGE"<<endl;
                                break;
                                case CROSS_EDGE: cout<<"("<<*itr1<<"->"<<*itr2<<") : CROSS_EDGE"<<endl;
                                break;
                                default:
                                break;
                            }
                        }
                        if(back_edge_present) break;
                    }
                    if(back_edge_present) break;
                }
                cout<<endl;
                if(back_edge_present) {
                    cout<<"Graph contains a directed cycle: ";
                    int bktrace_vertex = *itr1;
                    cout<<*itr2<<"<-";
                    do {
                        cout<<bktrace_vertex<<"<-";
                        bktrace_vertex = G.pi[bktrace_vertex];
                    } while(bktrace_vertex!=*itr2);
                    cout<<*itr2<<endl;
                }
                traversal.clear();
            }
            if(back_edge_present) break;
        }

        if(!back_edge_present) cout<<"Topological Sorting: "<<ts<<endl;
        fclose(stdin);
    }
    return 0;
}
