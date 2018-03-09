#include<iostream>
#include<string>
using namespace std;

#ifndef BST     // Binary Search Trees
#define BST

struct trunk{
	trunk *prev;
	string str;
	trunk(trunk *prev, string str) {
		this->prev = prev;
		this->str = str;
	}
};
// Helper function to print branches of the binary tree
void show_trunks(trunk *p){
	if (p == nullptr)
		return;
	show_trunks(p->prev);
    std::cout<< p->str ;
}


template <typename T>
struct bst_node {
    T key;
    bst_node<T>* left ;
    bst_node<T>* right ;
    bst_node<T>* parent ;
    
    bst_node( 
        const T & ele , bst_node<T>* lt , 
        bst_node<T>* rt ,  bst_node<T>* p):
        key{ele}, left{lt} ,  right{rt} ,
        parent{p}{}
    ~bst_node(){}
};

std::ostream& operator<<(std::ostream& ostr, const bst_node<int>* b) {
    ostr << b->key ;
    return ostr;
}


template <typename Key>
class bst {
    /*Private Members and Functions: can be only accessed by member functions*/
    bst_node<Key>* root;        /*Root of the tree*/
    
    /*returns the pointer to the node containing the key*/
    bst_node<Key>* get_node_containing(const Key &k) const {
        bst_node<Key>* x = root;
        while(x!=nullptr and k!=x->key){
            if(k < x->key) x = x->left;
            else x = x->right;
        }
        return x;
    }
    
    /*Print the binary tree*/
    void print_tree(bst_node<Key>* sub_tree_root, trunk* prev, bool is_left) {
        if(sub_tree_root == nullptr) return ;
        string prev_str = "    ";
        trunk *tnk = new trunk(prev , prev_str);
        print_tree(sub_tree_root->left , tnk , true);
        // if(prev == nullptr) tnk->str = "---";
        if(!prev) tnk->str = "-->";
        else if(is_left) {
            tnk->str = ".-->";
            prev_str = "   |";
        } else {
            tnk->str = "`-->";
            prev->str = prev_str;
        }
        show_trunks(tnk);
        cout<<sub_tree_root->key<<endl;
        //if(prev!=nullptr) { prev->str = prev_str; }
        if(prev) { prev->str = prev_str; }
        tnk->str = "   |";
        print_tree(sub_tree_root->right , tnk , false);
        delete tnk;
    }
        
    /*Clear the sub tree rooted at x*/
    void clear_sub_tree(bst_node<Key> *x){
        if(x==nullptr) return ;
        clear_sub_tree(x->left);
        clear_sub_tree(x->right);
        delete x;
    }
    
    /*returns the pointer to the minimum key bst_node*/
    bst_node<Key>* get_min(bst_node<Key>* x) const {
        if(x!=nullptr)
            while(x->left != nullptr) {
                x = x->left;
            }
        return x;
    }

    /*returns the pointer to the maximum key bst_node*/
    bst_node<Key>* get_max(bst_node<Key>* x) const {
        if(x!=nullptr) 
            while(x->right != nullptr) {
                x = x->right;
            }
        return x;
    }
    
    /*utility function to aid remove function: algorithm from thomas cormen*/
    void transplant(bst_node<Key>* u, bst_node<Key>* v) {
        if(u->parent  == nullptr ){ root = v; }
        else if (u == u->parent->left) { u->parent->left = v; }
        else u->parent->right = v;
        if(v!=nullptr) v->parent = u->parent;
    }

    /*removes a node in the tree*/
    void remove(bst_node<Key>* z) {
        // assuming the z is in tree
        // if(z==nullptr || !contains(z->key))   return ;
        if(z->left == nullptr)  transplant(z , z->right);
        else if(z->right == nullptr) transplant(z , z->left);
        else {
            bst_node<Key>* y = get_min(z->right);
            if(y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z , y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    /*in order traversal : produces a sorted result*/
    void in_order_traversal(bst_node<Key>* x) const {
        if(x!=nullptr){
            in_order_traversal(x->left);
            cout<<x->key<<" ";
            in_order_traversal(x->right);
        }
    }

    /*can be used to get postfix notation of an expression*/
    void post_order_traversal(bst_node<Key>* x) const {
        if(x!=nullptr) {
            post_order_traversal(x->left);
            post_order_traversal(x->right);
            cout<<x->key<<" ";
        }
    }
    /*can be used to get prefix notation of an expression*/
    void pre_order_traversal(bst_node<Key>* x) const {
        if(x!=nullptr) {
            cout<<x->key<<" ";
            pre_order_traversal(x->left);
            pre_order_traversal(x->right);
        }
    }

    /*returns pointer to the node containing the predecessor of the key*/
    bst_node<Key>* predecessor(bst_node<Key>* x) const {
        if(x==nullptr) return nullptr;
        if(x->left != nullptr) return get_max(x->left);
        bst_node<Key>* y = x->parent;
        while(y!=nullptr and x==y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }
    /*returns pointer to the node containing the successor of the key*/
    bst_node<Key>* successor(bst_node<Key>* x) const {
        if(x==nullptr) return nullptr;
        if(x->right != nullptr) return get_min(x->right);
        bst_node<Key>* y = x->parent;
        while(y!=nullptr and x==y->right) {
            x = y;
            y = y->parent ;
        }
        return y;
    }

public:
    /*Public functions : can be accessed by anybody*/

    /*Constructor*/
    bst () { root = nullptr; }

    /*returns true if tree is empty*/
    bool empty() const { return (root == nullptr); }

    /*de-allocate the memory allocated to the tree*/
    void clear(){
        clear_sub_tree(root);
        // delete root ;
        root = nullptr;
    }

    /*returns true if the tree contains the key*/
    bool contains(const Key &k) const {
        bst_node<Key>* x = root;
        while(x!=nullptr){
            if(k < x->key) x = x->left;
            else if(k > x->key) x = x->right;
            else return true;   // match
        }
        return false;
    }

    /*insert the key avoiding duplications*/
    void insert(const Key &k) {
        if(contains(k)){
            cout<<"Avoiding Duplicate Insertion"<<endl;
            return; 
        }
        bst_node<Key>* x = root;
        bst_node<Key>* z = new bst_node<Key>{k , nullptr, nullptr, nullptr};
        bst_node<Key>* y = nullptr;

        while(x!=nullptr) {
            y = x;
            if(z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if(y==nullptr) root = z;    // tree was empty
        else if (z->key < y->key) y->left = z;
        else y->right = z;
    }

    /*public function: wrapper for the remove function*/
    void remove(const Key &k) {
        bst_node<Key>* z = get_node_containing(k);
        if(z!=nullptr) remove(z);
        else cout<<"Can't remove: tree doesn't contain this key."<<endl;
    }
    
    /*public functions: wrapper for the get_min/get_max function*/
    bst_node<Key>* get_min() const { return get_min(root); }
    bst_node<Key>* get_max() const { return get_max(root); }

    /*wrapper*/
    bst_node<Key>* predecessor(const Key &k) const {
        bst_node<Key>* x = get_node_containing(k);
        return predecessor(x);
    }

    /*wrapper*/
    bst_node<Key>* successor(const Key &k) const {
        bst_node<Key>* x = get_node_containing(k);
        return successor(x);
    }

    /*wrapper*/
    void in_order_traversal() const {
        in_order_traversal(root);
        cout<<endl;
    }
    /*wrapper*/
    void post_order_traversal() const {
        post_order_traversal(root);
        cout<<endl;
    }
    /*wrapper*/
    void pre_order_traversal() const {
        pre_order_traversal(root);
        cout<<endl;
    }
    
    /*wrapper*/
    void print_tree(){
        print_tree(root, nullptr, false);
    }
    
    /*Destructor*/
    ~bst() {clear();}
};

#endif // BST
