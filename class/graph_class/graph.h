#include<iostream>
#include "list.h"

using namespace std;


#ifndef GRAPH_H
#define GRAPH_H

struct adj_list_node {
    int node_num;
    int weight;
    adj_list_node(int n , int w=1) : node_num{n} , weight{w} {}
};

bool compare_adj_list_node(adj_list_node* a , adj_list_node* b) {
    return (a->node_num!=b->node_num);
}

void display_adj_list_node(adj_list_node* a) {
    cout<<"{"<<a->node_num<<":"<<a->weight<<"} ";
}

class graph {
    int total_vertex;
    list *adj_list;

public:
    int get_total_vertex(){
        return total_vertex;
    }

    /* initializes the graph */
    graph(int V) {
        total_vertex=V;
        adj_list = new list[V];
        for(int i=0; i<V; i++) {
            initialize_list(&adj_list[i]);
        }
    }
    /* removes the edge from the vertex x to the vertex y, if it is there*/
    void remove_edge(int x, int y) {
        // necessary checks for the following function to work bug free
    	// self directed edges are not allowed : i.e x != y
    	if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y){
            adj_list_node p(y);
            node *nd = get_node(&adj_list[x] , (COMPARE)compare_adj_list_node , &p);
    		if(nd!=NULL) remove_node(&adj_list[x], nd);
        }
    }

    /* adds the edge from the vertex x to the vertex y, if it is not there*/
    void add_edge(int x, int y, int w=1) {
        if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y && !adjacent(x , y)){
            adj_list_node* ptr = new adj_list_node{y , w};
            push_back(&adj_list[x] , ptr);
        }
    }

    /* print all vertices y such that there is an edge from the vertex x to the vertex y */
    void display_neighbors(int x) {
        // prints all the neighbours of the vertex 'x'
        if(0<=x && x<total_vertex){
            display_list(&adj_list[x] , (DISPLAY)display_adj_list_node);
        }
    }

    /* tests whether there is an edge from the vertex x to the vertex y */
    bool adjacent(int x, int y) {
        if(0<=x && x<total_vertex && 0<=y && y<total_vertex && x!=y){
            adj_list_node tmp(y);
            return (contains(&adj_list[x] , (COMPARE) compare_adj_list_node , &tmp)!=0);
        }
        else return false;
    }

    /* clear the memory allocated to the graph */
    void clear() {
        for(int i=0; i<total_vertex ; i++) {
    		clear_list(&adj_list[i]);	       // clear the adjacent list
    	}
    	total_vertex = 0;                      // set the vertex count to zero
    	delete [] adj_list;					   // free the adjacent list array
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
