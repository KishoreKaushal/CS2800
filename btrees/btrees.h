#include<iostream>

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

    ~btree_node() {
        delete [] keys;
        delete [] c;
    }

    // friend class btrees;
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
};


#endif // BTREES