#include<iostream>

#ifndef UNION_FIND
#define UNION_FIND

class union_find {
private:
    int* p;         // parent
    int* rank;      // height of the subtree
    int* set_size;
    unsigned int num_sets;  // total Disjoint sets

public:

    union_find(int N=0) {
        num_sets = N;
        set_size = new int[N];
        rank = new int[N];
        p = new int[N];
        for(int i=0; i<N; ++i) {
            p[i] = i;
            rank[i] = 0;
            set_size[i] = 1;
        }
    }

    void clear() {
        delete [] p;
        delete [] rank;
        delete [] set_size;
        num_sets = 0;
    }

    ~union_find(){
        clear();
    }

    // path compression heuristic,
    int find_set(int i) {
        return (p[i] == i) ? i : (p[i] = find_set(p[i]));
    }

    bool is_same_set(int i, int j) {
        return find_set(i) == find_set(j);
    }

    // union by rank heuristic
    void union_set(int i, int j) {
        if(!is_same_set(i,j)) {
            num_sets--;
            int x = find_set(i) , y = find_set(j);
            // rank is used to keep the tree short
            if(rank[x] > rank[y]) {
                p[y] = x ;
                set_size[x]+=set_size[y];
            } else {
                p[x] = y ;
                set_size[y] += set_size[x];
                if(rank[x] == rank[y]) rank[y]++;
            }
        }
    }

    unsigned int num_disjoint_sets() { return num_sets; }
    int size_of_set(int i) { return set_size[find_set(i)]; }
};

#endif  // UNION_FIND
