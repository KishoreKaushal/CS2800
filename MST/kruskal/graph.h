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


struct edge {
    int u;
    int v;
    int wt;
    edge(int WT=-1, int U=-1, int V=-1):u{U}, v{V} , wt{WT} {}

    bool operator<= (const edge &e) { return (wt <= e.wt); }
    bool operator> (const edge &e) { return (wt > e.wt); }
    void operator=(const edge &e) {
        u = e.u;
        v = e.v;
        wt = e.wt;
    }
};

struct edge_list {
    edge *e;
    int num_edges;
    edge_list(int N=0){
        if(N!=0) e = new edge[N];
        else e = nullptr;
        num_edges=N;
    }
    ~edge_list() {
        if(e!= nullptr) delete [] e;
        num_edges=0;
    }
};

ostream& operator<<(std::ostream& ostr, edge_list &E) {
    for (int i=0; i<E.num_edges; ++i) {
        ostr<<"\t{ \033[1;32m("<<E.e[i].u<<" , "<<E.e[i].v<<")\033[0m : \033[1;33m "<<E.e[i].wt<<"\033[0m } ,"<<endl;
    }
    return ostr;
}


class graph {
public:
    int total_vertex;
    int  *previsit;  // previsit timing : used in the DFS
    int  *postvisit; // postvisit timing : will be used in the DFS
    int *pi;        // DFS caller
    int clock;

    Vector < Vector<adj_list_node> > adj_list;
    Vector <edge> mst;
    int *wt_i_prev_i;

    int get_total_vertex(){
        return total_vertex;
    }

    /* initializes the graph */
    graph(int V) :  total_vertex{V} , clock{0} {
        previsit = new int[V]();
        postvisit = new int[V]();
        wt_i_prev_i = new int[V]();
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
        mst.clear();
        delete [] previsit;
        delete [] postvisit;
        delete [] pi;
        delete [] wt_i_prev_i;
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
