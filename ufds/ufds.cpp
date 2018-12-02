#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

class union_find {
public:
    vector<int> rank;
    vector<int> parent;

    union_find(int N):rank(N,0), parent(N,0){
        // equivalent to make-set for each element in the beginning
        // for (int i=0; i<N; ++i){
        //     make_set(i);
        // }
        iota(parent.begin(), parent.end() , 0);
    }

    void make_set(int a){
        parent[a] = a;
    }

    int find_set(int a){
        if (parent[a] == a) return a;
        // path compression heuristic
        return parent[a] = find_set(parent[a]);
    }

    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        // using the rank-heuristics
        if (a!=b){
            if (rank[a] < rank[b]) {
                swap(a,b);
            }
            // assuming rank[a] > rank[b]
            parent[b] = a;
            if (rank[a] == rank[b]){
                ++rank[a];
            }
        }
    }
};


int main(){
    union_find u(10);
    return 0;
}