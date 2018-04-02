#include<iostream>
#include<string>

using namespace std;

typedef unsigned int uint;

#ifndef BTREES
#define BTREES

#define MAX_KEYS(t) (2*t - 1)
#define MIN_KEYS(t) (t-1)

template <typename T>
struct btree_node {
    T *keys;            /* array of keys */
    int t;             /* minimum number of child for an internal node */
    bool leaf;          /* true when the node is leaf node */
    btree_node<T>** c;  /* array of child pointers*/
    int n;             /* current number of keys*/

    /*utility function to insert a new key in the subtree
     rooted with this node.
     Assumption: node must be non-full when this function is called.
    */
    void insert_non_full(const T &ele) {
        /*index of the rightmost element in the node: n-1 */
        int i = n-1; 
        if(leaf == true) {  /*if leaf node*/
            /*find the appropriate location to put the new key 
            at the same time shifting all the greater elements 
            one place to the right*/
            while(ele < keys[i] and i>=0 ) {
                keys[i+1] = keys[i];
                i--;
            }
            /*insert to the appropriate location*/
            keys[i+1] = ele;
            n++;
        } else {    /*if not the leaf node */
            /* find the appropriate child which may
            be going to have this element */
            while ( 0<=i and ele < keys[i]) {
                --i;
            }

            /*see if the found child is full*/ 
            if (c[i+1]->n == MAX_KEYS(t)) {
                /*if the child is full then split it*/
                split_child(i+1 , c[i+1]);
                /*shift the middle key of c[i] up 
                after the splitting , and divide 
                the rest into two equal parts*/

                /*if this new key is going to be 
                in the right part of the splitted child*/
                if(keys[i+1] < ele ) ++i;  
            }
            c[i+1]->insert_non_full(ele);
        }
    }

    /*
    split the child y of this node. 
    i : index of y in child array
    the child array must be full when 
    this function is called
    */
    void split_child(int i , btree_node<T>* y ) {
        /*allocate a new internal node to store t-1 keys of y*/
        btree_node<T>* z = new btree_node(y->t , y->leaf);
        /*set the size to number of elements it store*/
        z->n = t-1;
        
        /*copy the last t-1 keys of y to z*/
        for (int j=0; j<t-1; ++j) {
            z->keys[j] = y->keys[j+t];
        }
        /*copy the last t children of y to z*/
        if(y->leaf == false) {
            for(int j=0; j<t; ++j) {
                z->c[j] = y->c[j+t];
            }
        }
        /*reduce the number of keys in y*/
        y->n = t-1;
        /*since this node is going to have a new 
        child, create space of new child */
        for (int j = n; i+1 <= j ; --j) {
            c[j+1] = c[j];
        }

        /*link the new child to this node*/
        c[i+1] = z;

        /*a key of will move to this node. Find location 
        of new key and move all greater keys one space
        ahead */
        for (int j = n-1;  i <= j ; --j) {
            keys[j+1] = keys[j];
        }
        /*copy the middle key of y to this node*/
        keys[i] = y->keys[t-1];
        n++;
    }

// public:

    btree_node(const T &mindeg , bool lf) : t{mindeg} , leaf{lf} , n{0} {
        /*memory allocation*/
        keys = new int[2*t - 1];        /* (2*t - 1) : maximum number of keys that can be hold*/
        c = new btree_node<T>* [2*t];   /*  (2*t)   : maximum number of child pointers*/
    }

    /*returns nullptr if not found*/
    btree_node<T>* search(const T &data , const bool &print_flags=false)  {
        /*find the first key greater than or equal to data*/
        int i=0;
        for (i=0; i< n && data > keys[i] ; ++i) ;
        
        if(data == keys[i]) {
            if(print_flags) {cout<<",index:{"<<i<<"}"<<endl;}
            return this;    /*data is found*/
        }
        
        /*if this is leaf node there will be no child hence return NULL*/
        if(leaf) return nullptr;
        
        /*go to the appropriate child of the child of this node that may contain this data*/
        if(print_flags) {cout<<"->child:{"<<i<<"}"; }
        return c[i]->search(data , print_flags);
    }

    /*returns the index of the key that is greater or equal to k*/
    int find_key(const T  &k) {
        int i=0;
        while (i<n and keys[i] < k) ++i;
        return i;
    }

    /*function to traverse all the nodes in a subtree rooted with this node*/
    void traverse() const {
        int i;
        /* in total : n keys in this internal node 
        ans n+1 children
        */
        for (i=0; i< n; ++i) {
            /*traverse through first n keys and n children*/
            if(!leaf) {
                /*if this is not leaf traverse the 
                immediate left child before printing the key*/
                c[i]->traverse();
            }
            cout<<keys[i]<<" ";
        }
        /*printing the subtree rooted with the last child*/
        if(!leaf) {
            c[i]->traverse();
        }
    }


     /*borrows a key from the c[idx-1]-th node and place it in
    c[idx]th node*/
    void borrow_from_prev(int idx) {
        btree_node<T> *child = c[idx];
        btree_node<T> *sibling = c[idx-1];

        /*moving all key in child c[idx] one step ahead*/
        for (int i=child->n-1; i>=0 ; --i) {
            child->keys[i+1] = child->keys[i];
        }
        /*moving the child pointers one step ahead*/
        if(!child->leaf) {
            for (int i=child->n; i>=0 ; --i) {
                child->c[i+1] = child->c[i];
            }
        }
        child->keys[0] = keys[idx-1];
        
        if(!leaf) {
            /*sibling's last child becomes the first child of the c[idx]*/
            child->c[0] = sibling->c[sibling->n];
        }
        keys[idx-1] = sibling->keys[sibling->n-1];
        child->n +=1 ;
        sibling->n -=1;
        return ;
    }

    /*similarly this function borrows from the 
    c[idx+1]th node and place it in c[idx]th node*/
    void borrow_from_next(int idx) {
        btree_node<T>* child = c[idx];
        btree_node<T>* sibling = c[idx+1];
        child->keys[(child->n)] = keys[idx];

        if(!child->leaf) {
            child->c[child->n +1] = sibling->c[0];
        }
        keys[idx] = sibling->keys[0];

        /*moving all keys in the sibling to one step back*/
        for (int i=1; i<sibling->n; ++i){
            sibling->keys[i-1] = sibling->keys[i];
        }

        if(!child->leaf) {
            for (int i=1; i<sibling->n; ++i){
                sibling->c[i-1] = sibling->c[i];
            }
        }
        child->n +=1;
        sibling->n -=1;
        return;
    }



    /*to fill up the child node present in the given position 
    in the child array c[] if that child has less than t-1 keys*/
    void fill(int idx) {
        /*previous child c[idx-1] has more than t-1 keys, then borrow a key*/
        if (idx!=0 && c[idx-1]->n>=t){
            borrow_from_prev(idx);
        } else if (idx!=n && c[idx+1]->n>=t) {
        /*next child c[idx+1] has more than t-1 keys, borrow a key*/
            borrow_from_next(idx);
        } else {
        /*Merge C[idx] with its sibling
        if C[idx] is the last child, merge it with with its previous sibling, otherwise merge it with its next sibling*/
            if (idx != n){
                merge(idx);
            } else{
                merge(idx-1);
            }
        }
    }

    /*merges the idx-th child of the node with (idx+1) the child of the node*/
    void merge(int idx) {
        btree_node<T> *child = c[idx];
        btree_node<T> *sibling = c[idx+1];

        /* Pulling a key from the current node and inserting it into (t-1)th position of c[idx] child->keys[t-1] = keys[idx];
        */
        // Copying the keys from c[idx+1] to c[idx] at the end
        for (int i=0; i<sibling->n; ++i)
            child->keys[i+t] = sibling->keys[i];

        // Copying the child pointers from c[idx+1] to c[idx]
        if (!child->leaf) {
            for(int i=0; i<=sibling->n; ++i)
                child->c[i+t] = sibling->c[i];
        }

        // Moving all keys after idx in the current node one step before -
        // to fill the gap created by moving keys[idx] to c[idx]
        for (int i=idx+1; i<n; ++i)
            keys[i-1] = keys[i];

        // Moving the child pointers after (idx+1) in the current node one
        // step before
        for (int i=idx+2; i<=n; ++i)
            c[i-1] = c[i];

        // Updating the key count of child and the current node
        child->n += sibling->n+1;
        n--;

        // Freeing the memory occupied by sibling
        delete sibling;
        return;
    }

    /*returns the predecessor of the key where the key is present in the give index
    position in the node*/
    T predecessor(int idx) {
        btree_node<T> *cur = c[idx];
        while(!cur -> leaf) {
            cur = cur->c[cur->n];
        }
        return cur->keys[cur->n-1];
    }

    /*returns the successor of the key where the key is present in the give index
    position in the node*/
    T successor(int idx) {
        btree_node<T>* suc = c[idx+1];
        while(!suc->leaf) {
            suc = suc->c[0];
        }
        return suc->keys[0];
    }
   


    /*removes the key present in at the 
    given location in this node which is
    a leaf node*/
    void remove_from_leaf(int &idx) {
        for (int i=idx+1; i<n; ++i) {
            keys[i-1] = keys[i];
        }
        n--;
    }
    
    /*removes the key present in at the 
    given location in this node which is
    a non-leaf node*/
    void remove_from_non_leaf(int &idx) {
        int k = keys[idx];

        if(t <= c[idx]->n) {
            /*if the child preceding k has atleat t keys*/
            T pred = predecessor(idx);
            keys[idx] = pred;
            c[idx]->remove(pred);
        } else if(t <= c[idx+1]->n) {
            /*if the child c[idx+1] has atleast t keys*/
            T succ = successor(idx);
            keys[idx] = succ;
            c[idx+1]->remove(succ);
        } else {
            /*if both c[idx] and c[idx+1] has less than t keys, merge them*/
            merge(idx);
            /*remove the key in the resulting node*/
            c[idx]->remove(k);
        }
        return;
    }


    /*wrapper to remove a key in 
    subtree rooted with this node*/
    void remove(const T &k) {
        /*get the index of the key that is greater or equal to k*/
        int idx = find_key(k);
        
        if(idx < n and keys[idx] == k) {
            /*the key is present in this node*/
            if(leaf) remove_from_leaf(idx);
            else remove_from_non_leaf(idx);
        } else {
            if (leaf) {
                /*if this node is leaf 
                then key is not present in the tree*/
                cout<<"Key not present in the tree."<<endl;
                return;
            }
            bool flag = ( (idx==n)? true : false );

            /*child containing the key has less than `t` keys, fill that child*/
            if(c[idx]->n < t) {
                fill(idx);
            }

            if(flag and idx>n) {
                /* if the last child has been merged*/
                c[idx-1]->remove(k);
            } else {
                c[idx]->remove(k);
            }
        }
        return;
    }



    ~btree_node() {
        delete [] keys;
        delete [] c;
    }

};


template <typename T>
class btrees {
    int t;                  /*degree*/
    btree_node<T>* root;    /*root node*/
    
    public:
    /*Constructor*/
    btrees(int _t): t{_t}  ,root{nullptr} {}
    
    /*returns pointer to an internal node in the tree if 
    it contains the gicen key , else returns nullptr*/
    btree_node<T>* search(const T& ele , const bool &print_flags = false) const {
        if(print_flags) cout<<"root ";
        return (root == nullptr) ? nullptr : root->search(ele , print_flags);
    }

    /*prints the tree in a sorted order by performing 
    a in order traversal similar to a binary tree where 
    left child is printed before printing the parent and right 
    child is printed after the parent */
    void in_order_traversal(){
        if (root!=nullptr) root->traverse();
    };

    /*insert a new key into the tree*/
    void insert(const T &ele) {
        /*if tree is empty*/
        if(root == nullptr) {
            /*allocate a new node for the root*/
            root = new btree_node<T>(t , true);
            /*insert setep : set the root key[0] to the ele*/
            root->keys[0] = ele;
            /*current number of keys in the root*/ 
            root->n = 1;
        } else { /*if tree is not empty*/

            /*if root is full , tree grows in height*/
            if (root->n == MAX_KEYS(t)) {
                /*allocate new node for the root*/
                btree_node<T>* s = new btree_node<T>(t , false);
                /*make current root as the child 
                of this newly allocated node*/
                s->c[0] = root;
                /*split the current root and move 1 key to the 
                newly allocated node*/
                s->split_child(0 , root);
                /*new root has two children now. */
                int i=0;
                if(s->keys[0] < ele) ++i;
                s->c[i]->insert_non_full(ele);

                /*updating the tree root*/
                root = s;
            } else {
                /*if root is not full*/
                root->insert_non_full(ele);
            }
        }
    }
    
    bool contains(const T &ele) {
        return (search(ele , false)!=nullptr);
    }
    
    // void clear();
    ~btrees() { 
        // clear(); 
    }
    
    void print_tree(btree_node<T>* x, string prev_str){
        for(int i=0; i<x->n; i++){
            if(!x->leaf){
                cout << prev_str << "----.\n";
                print_tree(x -> c[i], prev_str + "    |");
                cout << prev_str << "----.\n";
            }
            cout << prev_str << x -> keys[i] << "\n";
            // cout << prev_str << "----.\n";
        }
        if(!x->leaf){
            cout << prev_str << "----.\n";
            print_tree(x -> c[x->n], prev_str + "    |");
            cout << prev_str << "----.\n";
        }
    }
    
    void print_tree(){
        if(root==nullptr) return;
        for(int i=0; i<50; i++) cout << "*"; cout <<endl<<endl;
        print_tree(root, "|");
        for(int i=0; i<50; i++) cout << "*"; cout <<endl<<endl;
    }
    void remove(const T& k) {
        if(root == nullptr) {
            cout<<"Tree is empty"<<endl;
            return;
        }
        root->remove(k);
        
        if(root->n == 0) {
            btree_node<T> *tmp = root;
            if(root->leaf) { root = nullptr; }
            else root = root->c[0];
            delete  tmp;
        }
        return;
    }
};


#endif // BTREES