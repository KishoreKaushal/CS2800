/******************************************/
/*  @KishoreKaushal                       */
/*  111601008                             */
/*  ( Unique ) B-Trees                    */
/*  main.cpp                              */
/******************************************/

/*          use this to compile and run:        */
/* g++ -std=c++11 -Wall -g main.cpp && ./a.out  */


#include<iostream>
#include<cstdlib>
#include<string>
#include "btrees.h"
using namespace std;

void insert_wrapper(btrees<int> &b) {
    int key;
    cout<<"Enter a Key: ";
    cin>>key;
    b.insert(key);
    // cout<<"New Tree: "<<endl;
    // b.print_tree();
    // cout<<endl;
}

void search_wrapper(btrees<int> &b) {
    int key;
    cout<<"Enter the Key: ";
    cin>>key;
    
    if(b.contains(key)) {
        bool print_flags = true;
        cout<<"Tree contains this key."<<endl;
        b.search(key , true);
    } else cout<<"Tree doesn't contains this key."<<endl;
    
}

void insert_random(btrees<int> &b) {
    int n;
    cout<<"Number of elements: ";
    cin>>n;
    while(n>0) {
        int ele = rand() % 200;
        cout<<"Inserting "<<ele<<"..."<<endl;
        b.insert(ele);
        n--;
    }
}


void disp_menu() {
    char str[250] = "\n---------------------------------------------------\n1. Insert 1 Key\n2. Insert n random Keys\n3. Search Key\n4. In-Order-Traversal\n5. Print Tree\n0. Exit\nEnter an Option: ";
    cout<<str<<endl;
}

int main(){
    int t;
    cout<<"Enter the `t` value: ";
    cin>>t;
    int op=1;
    btrees<int> b(t);
    while(op!=0) {
        disp_menu();
        cin>>op;
        switch (op) {
            case 0: break;
            case 1: insert_wrapper(b); break;
            case 2: insert_random(b); break;
            case 3: search_wrapper(b); break;
            case 4: cout<<"\nIn-Order-Traversal: "; b.in_order_traversal(); cout<<endl; break;
            case 5: b.print_tree(); break;
            default: cout<<"Wrong Choice."<<endl; break;
        }
    }

    return 0;
}