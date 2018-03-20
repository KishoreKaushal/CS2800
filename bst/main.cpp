/******************************************/
/*  @KishoreKaushal                       */
/*  111601008                             */
/*  ( Unique ) Binary Search Tree         */
/*  main.cpp                              */
/******************************************/

/*          use this to compile and run:        */
/* g++ -std=c++11 -Wall -g main.cpp && ./a.out  */


#include<iostream>
#include "bst.h"
using namespace std;

void disp_menu() {
    char str[250] = "\n1. Insert Key\t\t\t7. Predecessor\n2. Minimum Key\t\t\t8. Successor\n3. Maximum Key\t\t\t9. Search Key\n4. Delete Key\t\t\t365. Print Tree\n5. In-order traversal\t\t314. Clear Tree\n6. Post-Order traversal\t\t981. Insert n keys\n\t\t<911> Exit\nEnter Option: ";
    cout<<str<<endl;
}

void insert_key(bst<int> & btree) {
    int key;
    cout<<"Enter a Key: ";
    cin>>key;
    btree.insert(key);
    cout<<"New Tree: "<<endl;
    btree.print_tree();
    cout<<endl;
}

void minimum_key(const bst<int> &btree) {
    bst_node<int> *bnode = btree.get_min();
    if(bnode != nullptr) cout<<"Minimum: "<<bnode<<endl;
    else cout<<"error: no minimum key"<<endl;
}

void maximum_key(const bst<int> &btree) {
    bst_node<int> *bnode = btree.get_max();
    if(bnode != nullptr) cout<<"Maximum: "<<bnode<<endl;
    else cout<<"error: no maximum key"<<endl;
}

void delete_key(bst<int> &btree) {
    int key;
    cout<<"Enter the Key: ";
    cin>>key;
    btree.remove(key);
    cout<<"New Tree: "<<endl;
    btree.print_tree();
    cout<<endl;
}

void predecessor(const bst<int> &btree) {
    int key;
    cout<<"Enter the Key: ";
    cin>>key;
    bst_node<int>* bnode = btree.predecessor(key);
    if(bnode!=nullptr) cout<<"Predecessor: " <<bnode<<endl;
    else cout<<"no predecessor"<<endl;
}

void successor(const bst<int> &btree) {
    int key;
    cout<<"Enter the Key: ";
    cin>>key;
    bst_node<int>* bnode = btree.successor(key);
    if(bnode!=nullptr) cout<<"Sucessor: "<<bnode<<endl;
    else cout<<"no successor"<<endl;
}

void search_tree(const bst<int> &btree) {
    int key;
    cout<<"Enter the Key: ";
    cin>>key;
    if(btree.contains(key)) cout<<"Tree contains this key."<<endl;
    else cout<<"Tree doesn't contains this key."<<endl;
}

void insert_n_keys(bst<int> &btree) {
    int n, key;
    cout<<"Total Elements: "<<endl; cin>>n;
    cout<<"Enter "<<n<<" keys: ";
    for(int i=0; i<n; ++i) {
        cin>>key;
        btree.insert(key);
    }
    cout<<"New Tree: "<<endl;
    btree.print_tree();
    cout<<endl;
}

int main() {
    int op = 0;
    bst<int> btree;
    while(op!=911) {
        disp_menu();
        cin>>op;
        switch(op) {
            case 1: insert_key(btree);
                break;
            case 2: minimum_key(btree);
                break;
            case 3: maximum_key(btree);
                break;
            case 4: delete_key(btree);
                break;
            case 5: btree.in_order_traversal();
                break;
            case 6: btree.post_order_traversal();
                break;
            case 7: predecessor(btree);
                break;
            case 8: successor(btree);
                break;
            case 9: search_tree(btree);
                break;
            case 365: btree.print_tree(); cout<<endl;
                break;  
            case 314: btree.clear();
                break;
            case 981: insert_n_keys(btree);
                break;
            case 911:
                break;
            default: cout<<"Wrong Choice.."<<endl;
        }
    }
    return 0;
}

// int main(){
//     // int op = 0;
//     // disp_menu();
//     int arr[] = {27 , 14 , 35, 10, 19, 31, 42};
//     bst<int> btree ;    /*Declaration*/
//     cout<<"Before Insertion: "<<"btree.empty() : "<<btree.empty()<<endl;
//     for (int i=0; i<7; i++) {
//         btree.insert(arr[i]);    /*Insertion*/
//     }
//     cout<<"After Insertion: "<<"btree.empty() : "<<btree.empty()<<endl;
//     btree.print_tree(); /*print tree*/
//     btree.in_order_traversal();
//     bst_node<int>* bnode = btree.successor(42);
//     if(bnode!=nullptr) cout<<"Successor: "<<bnode<<endl;
//     bnode = btree.predecessor(10);
//     if(bnode!=nullptr) cout<<"Successor: "<<bnode<<endl;
//     // btree.clear();      /*clear tree*/
//     bnode = btree.get_max();
//     if(bnode!=nullptr) cout<<"MAX: "<<bnode<<endl;
//     bnode = btree.get_min();
//     if(bnode!=nullptr) cout<<"MIN: "<<bnode<<endl;
//     cout<<"Contains 35: "<<btree.contains(35)<<endl;
//     btree.insert(35);
//     cout<<"Contains 45: "<<btree.contains(45)<<endl;
//     btree.insert(45);
//     btree.print_tree(); /*print tree*/
    
//     btree.remove(27);

//     btree.print_tree(); /*print tree*/

//     btree.remove(35);

//     btree.print_tree(); /*print tree*/
    

//     // btree.clear();      /*clear tree*/
//     // cout<<"After Clearing: "<<"btree.empty() : "<<btree.empty()<<endl;
//     return 0;
// }