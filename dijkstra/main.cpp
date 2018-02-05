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


class min_heap {
public:

    Pair<int , int > H[MAXSIZE]; // heap array
    int size;       // heap size

    min_heap(): size{0} {}

    /* returns the minimum element present in the heap : the most prior element in the heap*/
    int extract_min(){
        if(size>0){
            Pair<int , int > minh(H[0]);
            H[0] = H[--size];
            min_heapify(0);
            return minh.second;
        }
        cout<<"ERROR: Heap Underflow"<<endl;
        return INT_MIN;
    }

    /*Returns true if the insertion is successful*/
    bool insert(Pair<int , int > data) {
        if(size<MAXSIZE){
            H[size] = data;
            // cout<<"Inserting Node: "<<data.second<<endl;
            int i = size;
            Pair<int , int > temp;
            while(i!=0 && H[PARENT(i)]>H[i]) {
                temp = H[i];
                H[i] = H[PARENT(i)];
                H[PARENT(i)] = temp;
                i = PARENT(i);
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
        // swap the smallest with the idx
        if(smallest != idx) {
            Pair<int , int > temp(H[idx]);
            H[idx] = H[smallest];
            H[smallest] = temp;
            min_heapify(smallest);
        }
    }

    /*To increase the priority of a certain element at a certain index*/
    void decrease_key(int idx , int new_key) {
        // cout<<"New Key for idx: "<<idx<<" : "<<new_key<<endl;
        if(new_key < H[idx].first){
            H[idx] = new_key;
            while(idx>0 && H[PARENT(idx)]>H[idx]) {
                // swap
                Pair<int , int > temp(H[idx]);
                H[idx] = H[PARENT(idx)];
                H[PARENT(idx)] = temp;
            }
        }
        else cout<<"Attempt to increase the key value using decrease_key()."<<endl;
    }

    int get_idx(int v) {
        for (int i=0; i<size; ++i) {
            if(H[i].second == v) {
                return i;
            }
        }
        return -1;
    }
    void print_heap() {
        cout<<"printing heap:"<<endl;
        for(int i=0 ; i<size; ++i) {
            cout<<H[i].first<<" "<<H[i].second<<endl;
        }
    }
    /* sets the size of teh heap to zero : which in priciple clears the heap*/
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

void Dijkstra(graph &G, int source , int dist[], int prev[]) {
    int u,v,wt;
    /*Creating a vertex set*/
    min_heap Q;
    bool *visited = new bool[G.get_total_vertex()];
    /* Initialization*/
    dist[source] = 0;
    for(int i=0; i<G.get_total_vertex(); ++i) {
        if(i!=source){
            dist[i] = INF;
        }
        prev[i] = UNDEFINED;
        visited[i] = false;
        Q.insert(Pair<int,int>(dist[i] , i));
    }

    // Q.print_heap();

    while(!Q.empty()) {
        /*Extract the node with the minimum distance from the source */
        u = Q.extract_min();
        visited[u] = true;
        for(Vector<adj_list_node>::iterator itr = G.adj_list[u].begin(); itr!=G.adj_list[u].end(); ++itr) {
            v = (*itr).node_num;
            if(!visited[v]) {
                wt = (*itr).weight;
                if(dist[u]+wt < dist[v]) {
                    dist[v] = dist[u]+wt;
                    prev[v] = u;
                    Q.decrease_key(Q.get_idx(v) , dist[v]);
                }
            }
        }
    }
    delete visited;
}


/* Printing the Dijkstra Algorithms Results*/
void print_dijkstra_results(graph &G, int prev[], int dist[], int source){
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
            Dijkstra(G, source, dist, prev);
            print_dijkstra_results(G, prev, dist, source);
            cout<<endl;
        // }

        delete dist;
        delete prev;
        fclose(stdin);
    }
    return 0;
}
