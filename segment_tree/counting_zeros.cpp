#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<utility>

using namespace std;

#define RIGHT(i) ((i*2 + 2))
#define LEFT(i) ((i*2 + 1))
#define MAXN (100000)

class segment_tree{
public:
    int size;
    vector<int> arr;
    vector<int> tree;
    segment_tree(int n){
        size = n;
        arr.reserve(n+1);
        tree.reserve(4*(n+1));
    }

    void build(){
        build(0, 0, size-1);
    }

    void build(int i, int tl, int tr){
        if (tl == tr) {
            tree[i] = (arr[tl]==0?1:0); /*1 if arr[tl] is 0*/
        } else {
            int tm = (tl + tr)/2;
            build(LEFT(i), tl, tm);
            build(RIGHT(i), tm+1, tr);
            /*combine*/
            tree[i] = tree[LEFT(i)] + tree[RIGHT(i)];
        }
    }

    void toggle(int pos){
        int new_val = arr[pos] = (arr[pos]==0?1:0);
        update(0, 0, size-1, pos, new_val);
    }

    void update(int pos, int new_val){
        arr[pos] = new_val;
        update(0, 0, size-1, pos, new_val);
    }

    void update(int i, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            tree[i] = (new_val==0?1:0);
        } else {
            int tm = (tl+tr)/2;
            if (pos <= tm) update(LEFT(i) , tl, tm, pos, new_val);
            else update(RIGHT(i), tm+1, tr, pos, new_val);
            /*combine*/
            tree[i] = tree[LEFT(i)] + tree[RIGHT(i)];
        }
    }

    int count_zero(int l, int r){
        return count_zero(0, 0, size-1, l, r);
    }

    int count_zero(int i, int tl, int tr, int l, int r){
        if (l > r) return 0;
        if (tl == l && tr == r) return tree[i];
        int tm = (tl + tr)/2;
        
        return count_zero(LEFT(i), tl, tm, l, min(r,tm))
                + count_zero(RIGHT(i), tm+1, tr, max(tm+1 , l), r);
    }

    int find_kth(int k){
        if (k > count_zero(0,size-1)) return -1;    /*no kth zero*/
        find_kth(0, 0, size-1, k);
    }

    int find_kth(int i, int tl, int tr, int k){
        if (tree[i] < k) return -1;
        if (tl == tr) return tl;
        int tm = (tl +  tr)/2;
        if (tree[LEFT(i)] >= k) return find_kth(LEFT(i), tl, tm, k);
        return find_kth(RIGHT(i), tm+1, tr, k-tree[LEFT(i)]);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.setf(ios::fixed); cout.precision(6);

    int N;  // size of the array
    int Q;  // number of the queries
    int T;  // type of query
    int L,R,P,K;
    // three types of the query is possible:
    // 1. count the number of zeros in the given range  -   L , R
    // 2. toggle the bits at position P                 -   P
    // 3. find the index of the Kth zero                -   K

    
    cin>>N>>Q;

    segment_tree seg(N);
    for (int i=0; i<N; ++i){
        cin>>seg.arr[i];
    }
    seg.build();

    for(int i=0; i<Q; ++i){
        cin>>T;
        switch(T){
            case 1: cin>>L>>R;  cout<<seg.count_zero(L,R)<<endl;
                break;
            case 2: cin>>P;     seg.toggle(P);
                break;
            case 3: cin>>K;     cout<<seg.find_kth(K)<<endl;
                break;
            default:
                break;
        }
    }

    return 0;
}