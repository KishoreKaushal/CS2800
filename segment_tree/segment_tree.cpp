#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<utility>

#define LEFT(i) (2*i)
#define RIGHT(i) (2*i + 1)

using namespace std;


/*segment tree for range-sum queries*/
class segment_tree {
public:
    int size;
    vector<int> arr;
    vector<int> tree;

    segment_tree(int n){
        arr.reserve(n+1);
        tree.reserve(4*(n+1));
        build();
    }

    void build(){
        build(0,0,size-1);
    }

    void build(int i, int tl, int tr){
        if (tl == tr) {
            tree[i] = arr[tl];
        } else {
            int tm = (tl+tr)>>1;
            build(LEFT(i), tl, tm);
            build(RIGHT(i), tm + 1, tr);
            /*combine step*/
            tree[i] = tree[LEFT(i)] + tree[RIGHT(i)];
        }
    }

    /*Query for [l,r]*/
    int sum(int l, int r){
        return sum(0,0,size-1,l,r);
    }

    int sum(int i, int tl, int tr, int l, int r){
        if (l > r) return 0;
        if (tl == l && tr == r) return tree[i];
        int tm = (tl+tr)>>1;
        
        // if (tl <= l && r <= tm) return sum(LEFT(i), tl, tm, l, r);
        // if (tm + 1 <= l && r <= tr) return sum(RIGHT(i), tm+1, tr, l, r);
        
        return sum(LEFT(i), tl, tm, l, min(r,tm)) 
                + sum(RIGHT(i), tm+1, tr, max(l, tm+1), r);
    }

    void update(int pos, int new_val){
        arr[pos] = new_val;
        update(0,0,size-1,pos,new_val);
    }

    void update(int i, int tl, int tr, int pos, int new_val){
        if (tl == tr) {
            tree[i] = new_val;
        } else {
            int tm = (tl + tr)>>1;
            if (pos <= tm) update(LEFT(i), tl, tm, pos, new_val);
            else update(RIGHT(i), tm+1, tr, pos, new_val);
            /*update combine*/
            tree[i] = tree[LEFT(i)] + tree[RIGHT(i)];
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.setf(ios::fixed); cout.precision(6);

    return 0;
}