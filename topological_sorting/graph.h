#include<iostream>
// #include "list.h"
#include "vector.h"

using namespace std;


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

ostream& operator<<(std::ostream& ostr, Vector<adj_list_node>& list)
{
    for(Vector<adj_list_node>::iterator itr = list.begin(); itr!=list.end(); ++itr) {
        ostr<<(*itr).node_num<<" ";
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
    int total_vertex;
    // list *adj_list;
    Vector < Vector<adj_list_node> > adj_list;
public:
    int get_total_vertex(){
        return total_vertex;
    }

    /* initializes the graph */
    // : adj_list(V , Vector<adj_list_node>(0 , adj_list_node(-1 , -1)))
    graph(int V)  {
        total_vertex=V;
        for(int i=0; i<V; i++) {
            adj_list.push_back(Vector<adj_list_node>(0 , adj_list_node(-1 , -1)));
        }
    }

    /* removes the edge from the vertex x to the vertex y, if it is there*/
    void remove_edge(int x, int y) {
        // necessary checks for the following function to work bug free
    	// self directed edges are not allowed : i.e x != y
    	if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y){
            adj_list_node p(y);
            bool present = false;
            int idx=0;
            for(Vector<adj_list_node>::iterator itr = adj_list[x].begin(); itr!=adj_list[x].end(); ++itr) {
                if(*itr == p) {
                    present = true;
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

    /* clear the memory allocated to the graph */
    void clear() {
        for(int i=0; i<total_vertex ; i++) {
    		adj_list[i].clear();      	       // clear the adjacent list
    	}
    	total_vertex = 0;                      // set the vertex count to zero
    	adj_list.clear();					   // free the adjacent list array
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
    }
};

#endif // GRAPH_H
