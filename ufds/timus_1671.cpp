#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<utility>

using namespace std;

class union_find {
public:
    vector<int> rank;
    vector<int> parent;
    int conn_comp;

    union_find(int N):rank(N,0), parent(N,0){
        iota(parent.begin(), parent.end() , 0);
        conn_comp=N;
    }

    void make_set(int a){
        parent[a] = a;
    }

    int find_set(int a){
        if (parent[a] == a) return a;
        return parent[a] = find_set(parent[a]);
    }

    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if (a!=b){
            if (rank[a] < rank[b]) {
                swap(a,b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]){
                ++rank[a];
            }
            --conn_comp;
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cout.setf(ios::fixed); cout.precision(6);

    int N, M, Q, p, q, temp;
    
    vector<pair<bool, pair<int, int>> > conn;
    vector<int> thread_cut;
    vector<int> ans;

    conn.reserve(100001);
    thread_cut.reserve(100001);
    ans.reserve(100001);

    cin>>N>>M;
    for (int i=0; i<M; ++i){
        cin>>p>>q;
        conn[i] = make_pair(true, make_pair(p-1,q-1));
    }
    
    cin>>Q;
    for (int i=0; i<Q; ++i){
        cin>>thread_cut[i];
        conn[thread_cut[i]-1].first = false;
    }
    
    union_find web(N);

    for (int i=0; i<M; ++i){
        if (conn[i].first){
            web.union_sets(conn[i].second.first , conn[i].second.second);
        }
    }

    for (int j=Q-1; j>=0; --j){        
        ans[j] = web.conn_comp;
        temp = thread_cut[j]-1;
        conn[temp].first = true;
        web.union_sets(conn[temp].second.first , conn[temp].second.second);
    }
    
    cout<<ans[0];
    for (int i=1; i<Q; ++i){
        cout<<" "<<ans[i];
    }

    return 0;
}