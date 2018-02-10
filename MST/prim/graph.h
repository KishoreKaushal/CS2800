#include<iostream>
// #include "list.h"
#include "vector.h"

using namespace std;

#ifndef PAIR
#define PAIR

/* Currently used for the purpose of storing the node with distance information in the heap*/
template <typename T1 , typename T2>
struct Pair {
    T1 first;   // key value (in this context the distance from the source)
    T2 second;  // main value (in this context the node number )

    Pair(T1 fst, T2 sec): first{fst} , second{sec} {}
    Pair(const Pair<T1, T2> &P){
        first = P.first;
        second = P.second;
    }
    Pair(){}

    /*Operator Overloading*/
    void operator=(const Pair<T1, T2> &P) {
        first = P.first;
        second = P.second;
    }

    void operator=(const T1 &fst) {
        first = fst;
    }

    bool operator== (const Pair<T1, T2> &P) {
        return (first == P.first);
    }

    bool operator!= (const Pair<T1, T2> &P) {
        return (first != P.first);
    }

    bool operator< (const Pair<T1, T2> &P) {
        return (first < P.first);
    }
    bool operator> (const Pair<T1, T2> &P) {
        return (first > P.first);
    }

};

#endif // PAIR

#ifndef GRAPH_H
#define GRAPH_H

struct adj_list_node {
    int node_num;
    int weight;
    adj_list_node(int n , int w=1) : node_num{n} , weight{w} {}
    bool operator== (const adj_list_node &node) {
        return (node_num == node.node_num);
    }
};

ostream& operator<<(std::ostream& ostr, Vector<adj_list_node>& list) {
    for(Vector<adj_list_node>::iterator itr = list.begin(); itr!=list.end(); ++itr) {
        ostr<<"{"<<(*itr).node_num<<":"<<(*itr).weight<<"} , ";
    }
    return ostr;
}


bool compare_adj_list_node(adj_list_node* a , adj_list_node* b) {
    return (a->node_num!=b->node_num);
}

void display_adj_list_node(adj_list_node* a) {
    cout<<"{"<<a->node_num<<":"<<a->weight<<"} ";
}

class graph {
public:
    int total_vertex;
    int  *previsit;  // previsit timing : used in the DFS
    int  *postvisit; // postvisit timing : will be used in the DFS
    int *pi;        // DFS caller
    int clock;

    Vector < Vector<adj_list_node> > adj_list;
    Vector <Pair<int, int>> mst;

    int get_total_vertex(){
        return total_vertex;
    }

    /* initializes the graph */
    graph(int V) :  total_vertex{V} , clock{0} {
        previsit = new int[V]();
        postvisit = new int[V]();
        pi = new int[V]();
        for(int i=0; i<V; i++) {
            adj_list.push_back(Vector<adj_list_node>(0 , adj_list_node(-1 , -1)));
            // previsit[i] = postvisit[i] = -1;
        }
    }

    /* removes the edge from the vertex x to the vertex y, if it is there*/
    void remove_edge(int x, int y) {
        // necessary checks for the following function to work bug free
    	// self directed edges are not allowed : i.e x != y
    	if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y){
            adj_list_node p(y);
            //bool present = false;
            int idx=0;
            for(Vector<adj_list_node>::iterator itr = adj_list[x].begin(); itr!=adj_list[x].end(); ++itr) {
                if(*itr == p) {
                    //present = true;
                    adj_list[x].erase(idx);
                    break;
                }
                idx++;
            }
        }
    }

    /* adds the edge from the vertex x to the vertex y, if it is not there*/
    void add_edge(int x, int y, int w=1) {
        if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y && !adjacent(x , y)){
            adj_list[x].push_back(adj_list_node(y,w));
        }
    }

    /* print all vertices y such that there is an edge from the vertex x to the vertex y */
    void display_neighbors(int x) {
        // prints all the neighbours of the vertex 'x'
        if(0<=x && x<total_vertex){
            cout<<adj_list[x]<<endl;
        }
    }

    /* tests whether there is an edge from the vertex x to the vertex y */
    bool adjacent(int x, int y) {
        if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y){
            adj_list_node tmp(y);
            for(Vector<adj_list_node>::iterator itr = adj_list[x].begin(); itr!=adj_list[x].end(); ++itr) {
                if(*itr == tmp) {
                    return true;
                }
            }
            return false;
        }
        else return false;
    }

    void reset_previsit_postvisit() {
        for (int i=0; i<total_vertex; ++i) {
            postvisit[i] = previsit[i] = 0;
            pi[i] = -1;
        }
        clock = 0;
    }

    /* clear the memory allocated to the graph */
    void clear() {
        for(int i=0; i<total_vertex ; i++) {
    		adj_list[i].clear();      	       // clear the adjacent list
    	}
    	total_vertex = 0;                      // set the vertex count to zero
    	adj_list.clear();					   // free the adjacent list array
        delete [] previsit;
        delete [] postvisit;
        delete [] pi;
    }

    void print(){
    	for(int i=0; i<total_vertex; i++) {
    		printf("V:%3d , Adj.List: ", i);
    		display_neighbors(i);
    	}
    }

    bool empty() { return total_vertex==0; }

    ~graph() {
        if(total_vertex!=0) clear();
        // delete [] previsit;
        // delete [] postvisit;
    }
};

#endif // GRAPH_H
