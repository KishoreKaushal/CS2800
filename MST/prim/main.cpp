/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	main.cpp      						*/
/*	Objective	:	Dijkstra Algorithm           		*/
/********************************************************/

/* Undirected graph */

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include "vector.h" // vector implementation
#include "graph.h"  // graph implementation

#define MAXSIZE (200)
#define INF (999999)
#define UNDEFINED (-1)
#define PARENT(i) ((int)((i-1)/2))
#define LEFT(i) ((int)(2*i + 1 ))
#define RIGHT(i) ((int)(2*i + 2 ))

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

class min_heap {
public:

    Pair<int , int > H[MAXSIZE]; // heap array
    int size;       // heap size
    int node_index[MAXSIZE];    // to make the decrease_key a constant time operation
    min_heap(): size{0} {
        /*Initialization*/
        for (int i=0; i<MAXSIZE; ++i){
            node_index[i] = -1;
        }
    }

    /* returns the minimum element present in the heap : the most prior element in the heap*/
    int extract_min(){
        if(size>0){
            Pair<int , int > minh(H[0]);
            H[0] = H[--size];
            /*Modifying the node index*/
            node_index[H[0].second ] = 0;
            node_index[minh.second] = -1;
            min_heapify(0);
            return minh.second;
        }
        cout<<"ERROR: Heap Underflow"<<endl;
        return INT_MIN;
    }

    bool append_to_heap_array(Pair<int,int> data) {
        if(size<MAXSIZE) {
            H[size] = data;
            node_index[data.second] = size;
            ++size;
            return true;
        }
        return false;
    }

    /*Returns true if the insertion is successful*/
    bool insert(Pair<int , int > data) {
        if(size<MAXSIZE){
            H[size] = data;
            // cout<<"Inserting Node: "<<data.second<<endl;
            int idx = size;
            Pair<int , int > temp;
            while(idx!=0 && H[PARENT(idx)]>H[idx]) {
                // swap idx and change the index value in the node index
                int i = node_index[H[PARENT(idx)].second];
                int j = node_index[H[idx].second];
                // swap the index
                node_index[H[PARENT(idx)].second] = j;
                node_index[H[idx].second] = i;

                temp = H[idx];
                H[idx] = H[PARENT(idx)];
                H[PARENT(idx)] = temp;
                idx = PARENT(idx);
            }
            ++size;
            return true;
        }
        return false;
    }

    /*Function to maintain the heap property of the data structure*/
    void min_heapify(int idx) {
        int smallest = idx;
        if(LEFT(idx)<size && H[LEFT(idx)]< H[smallest])
            smallest = LEFT(idx);
        if(RIGHT(idx)<size && H[RIGHT(idx)]< H[smallest])
            smallest = RIGHT(idx);
        if(smallest != idx) {
            // swap the smallest with the idx and change the index value in the node index
            int i = node_index[ H[smallest].second ];
            int j = node_index[H[idx].second];
            // swap the index
            node_index[ H[smallest].second ] = j;
            node_index[H[idx].second] = i;
            // swap the data
            Pair<int , int > temp(H[idx]);
            H[idx] = H[smallest];
            H[smallest] = temp;
            min_heapify(smallest);
        }
    }

    /*To increase the priority of a certain element at a certain index*/
    void decrease_key(int idx , int new_key) {
        // cout<<"New Key for idx: "<<idx<<" : "<<new_key<<endl;
        if(idx==-1) return ;
        if(new_key < H[idx].first){
            // int v = H[idx].second;  // vertex number
            H[idx] = new_key;
            while(idx>0 && H[PARENT(idx)]>H[idx]) {
                // swap the smallest with the idx and change the index value in the node index
                int i = node_index[H[PARENT(idx)].second];
                int j = node_index[H[idx].second];
                // swap the index
                node_index[H[PARENT(idx)].second] = j;
                node_index[H[idx].second] = i;
                // swap with parent : and change the index of the PARENT
                Pair<int , int > temp(H[idx]);
                H[idx] = H[PARENT(idx)];
                H[PARENT(idx)] = temp;
                idx = PARENT(idx);
            }
        }
        else cout<<"Attempt to increase the key value using decrease_key()."<<endl;
    }

    int get_idx(int v) {
        return node_index[v];
    }
    void print_heap() {
        cout<<"printing heap:"<<endl;
        for(int i=0 ; i<size; ++i) {
            cout<<H[i].first<<" "<<H[i].second<<endl;
        }
    }
    /* sets the size of the heap to zero : which in priciple clears the heap*/
    void clear() {
        size = 0;
    }

    bool empty() {
        return (size==0);
    }
};

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

void prim(graph &G , int source ) {
    // Initialization
    int u,v,wt,idx_v;
    min_heap Q;
    bool *visited = new bool[G.get_total_vertex()];
    int *prev = new int[G.get_total_vertex()];

    for(int i=0; i<G.get_total_vertex(); ++i) {
        prev[i] = UNDEFINED;
        G.wt_i_prev_i[i] = INF;
        visited[i] = false;
        /*Appending the information into the heap :
        constant operation since the vertices are numbered from 0 to N-1*/
        Q.append_to_heap_array(Pair<int,int>(INF , i));
    }

    /*Initialization of the source vertex distance from the source */
    /* Decrease is a constant time operation because of maintaining
    the index array within the class of the min_heap */
    Q.decrease_key(Q.get_idx(source) , 0);

    while(!Q.empty()) {
        /*Extract the node with the minimum distance from the source */
        u = Q.extract_min();
        visited[u] = true;
        for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
            v = (*itr).node_num;
            wt = (*itr).weight;
            idx_v = Q.get_idx(v);
            if(!visited[v] && wt < Q.H[idx_v].first) {
                prev[v] = u;
                G.wt_i_prev_i[v] = wt;
                Q.decrease_key(idx_v , wt);
            }
        }
    }
    // construct & returns the edge list of the MST
    G.mst.clear();  // clearing the previous MST
    for(int i=0; i<G.total_vertex; ++i){
        if(i!=source){
            //cout<<prev[i]<<" "<<i<<endl;
            G.mst.push_back(Pair<int,int>(prev[i] , i));
        }
    }
    delete [] visited;
    delete [] prev;
}

// wrapper function for calling the prims algorithm
void print_mst(graph &G , int source) {
    prim(G , source);
    int total_weight = 0;
    cout<<"\033[1;31mMST-PRIM \033[0m{"<<endl;
    for(Vector<Pair<int, int>>::iterator itr = G.mst.begin(); itr!=G.mst.end(); ++itr) {
        cout<<"\t{ \033[1;32m("<<(*itr).first<<" , "<<(*itr).second<<")\033[0m : \033[1;33m "<<G.wt_i_prev_i[(*itr).second]<<"\033[0m } ,"<<endl;
        total_weight+=G.wt_i_prev_i[(*itr).second];
    }
    cout<<"}"<<endl;
    cout<<"Total Weight: "<<total_weight<<endl;
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
        int source=0;    // source vertex
        cout<<endl;
        cin>>source;

        print_mst(G, source);
        fclose(stdin);
    }
    return 0;
}
