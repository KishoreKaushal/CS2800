#include<iostream>
#include "bst.h"
using namespace std;

void disp_menu() {
    char str[200] = "1. Insert Key\n2. Minimum Key\n3. Maximum Key\n4. Delete Key\n5. In-order traversal\n6. Post-Order traversal\n7. Predecessor\n8. Successor\n9. Search Key\n10. Print Tree\n99. Exit";
    cout<<str<<endl;
}

int main(){
    // int op = 0;
    // disp_menu();
    int arr[] = {27 , 14 , 35, 10, 19, 31, 42};
    bst<int> btree ;    /*Declaration*/
    cout<<"Before Insertion: "<<"btree.empty() : "<<btree.empty()<<endl;
    for (int i=0; i<7; i++) {
        btree.insert(arr[i]);    /*Insertion*/
    }
    cout<<"After Insertion: "<<"btree.empty() : "<<btree.empty()<<endl;
    btree.print_tree(); /*print tree*/
    btree.in_order_traversal();
    bst_node<int>* bnode = btree.successor(42);
    if(bnode!=nullptr) cout<<"Successor: "<<bnode<<endl;
    bnode = btree.predecessor(10);
    if(bnode!=nullptr) cout<<"Successor: "<<bnode<<endl;
    // btree.clear();      /*clear tree*/
    bnode = btree.get_max();
    if(bnode!=nullptr) cout<<"MAX: "<<bnode<<endl;
    bnode = btree.get_min();
    if(bnode!=nullptr) cout<<"MIN: "<<bnode<<endl;
    cout<<"Contains 35: "<<btree.contains(35)<<endl;
    btree.insert(35);
    cout<<"Contains 45: "<<btree.contains(45)<<endl;
    btree.insert(45);
    btree.print_tree(); /*print tree*/
    
    btree.remove(27);

    btree.print_tree(); /*print tree*/

    btree.remove(35);

    btree.print_tree(); /*print tree*/
    

    // btree.clear();      /*clear tree*/
    // cout<<"After Clearing: "<<"btree.empty() : "<<btree.empty()<<endl;
    return 0;
}