#include<iostream>
#include<cstdlib>

using namespace std;

#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
struct vector_node {
   T val;
   vector_node<T> *next;
   vector_node<T> *prev;

   vector_node(T &the_val , vector_node<T>* the_next = nullptr, vector_node<T>* the_prev = nullptr)
   : val{the_val} , next{the_next} , prev{the_prev} {}

};

template <typename T>
class Vector {
    vector_node<T>* FRONT;
    vector_node<T>* BACK;
    int SIZE;

public:

    struct iterator {
        vector_node<T>* current ;

        iterator(vector_node<T>* vec_nd=nullptr) : current{vec_nd} {}

        const iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator result = *this;
            ++(*this);
            return result;
        }
        void operator=(const iterator &itr) {
            this.current = itr.current;
        }

        bool operator== (const iterator &itr) {
            return (current == itr.current);
        }

        bool operator!= (const iterator &itr) {
            return (current != itr.current);
        }

        T& operator*() { return current->val; }
    };

    Vector() { FRONT = nullptr; BACK = nullptr ; SIZE=0; }

    Vector(int n , T data) {
        SIZE = 0;
        FRONT = nullptr;
        BACK = nullptr ;
        for (int i=0; i<n; i++) {
            push_back(data);
        }
    }
    ~Vector() {  clear() ; }

    /* Returns 1 if the vector is empty */
    bool empty() {
        return (SIZE==0);
    }

    /* Clears the memory allocated to the vector */
    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

    /* Removes a node from the back */
    void pop_back() {
        if(SIZE!=0) {
            vector_node<T>* nd = BACK;
            if(FRONT == BACK ) {
                FRONT = BACK = nullptr;
            } else {
                BACK = BACK->prev;
                BACK->next = nullptr;
            }
            delete nd;
            SIZE--;
        } else {
            cout<<"ERROR: size is less than equal to zero"<<endl;
        }
    }

    /* Add the data to the back of the vector */
    void push_back(T data) {
        vector_node<T>* nd = new vector_node<T>(data, nullptr , BACK);
        if(nd!=nullptr) {
            if(SIZE==0) {
                FRONT = BACK = nd;
            } else {
                BACK->next = nd;
                BACK = nd;
            }
            SIZE++;
        } else {
            cout<<"ERROR: allocation failed"<<endl;
        }
    }

    /* Rempves the front node */
    void pop_front() {
        if(SIZE!=0) {
            vector_node<T>* nd = FRONT;
            if(FRONT == BACK) {
                FRONT = BACK = nullptr;
            } else {
                FRONT = FRONT->next;
                FRONT->prev = nullptr;
            }
            delete nd;
            SIZE--;
        } else {
            cout<<"ERROR: size is less than equal to zero"<<endl;
        }
    }

    /* Adds a data in the front of the list */
    void push_front(T data) {
        vector_node<T>* nd = new vector_node<T>(data , FRONT , nullptr) ;

        if(nd!=nullptr) {
            if(SIZE==0) {
                FRONT = BACK = nd;
            } else {
                FRONT->prev = nd;
                FRONT = nd;
            }
            SIZE++;
        }
    }

    /* Returns the size of the vector */
    int size() { return SIZE; }

    /* inserts a data at the desired index */
    void insert(T data , int index) {
        if(0 <= index && index < SIZE) {
            if(SIZE==0 || index == 0) {
                push_front(data);
            } else if(index == SIZE-1) {
                push_back(data);
            } else {
                vector_node<T>* nd = new vector_node<T>(data);
                vector_node<T>* node_crawl=FRONT;
                for (int i=0; i<index-1; i++) {
                    node_crawl = node_crawl->next;
                }
                nd->next = node_crawl->next;
                nd->prev = node_crawl;
                node_crawl->next = nd;
                nd->next->prev = nd;
                SIZE++;
            }
        } else {
            cout<<"ERROR: index out of bounds"<<endl;
            exit(0);
        }
    }

    /* Erase a data from the given index */
    void erase(int index) {
        if(0 <= index && index < SIZE) {
            if(SIZE==1 || index==0 ) {
                pop_front();
            } else if(index == SIZE-1) {
                pop_back();
            } else {
                vector_node<T>* node_crawl=FRONT;
                for (int i=0; i<index; i++) {
                    node_crawl = node_crawl->next;
                }
                node_crawl->next->prev = node_crawl->prev;
                node_crawl->prev->next = node_crawl->next;
                delete node_crawl;
                SIZE--;
            }
        } else {
            cout<<"ERROR: index out of bounds"<<endl;
            exit(0);
        }
    }

    // /* Returns a pointer to the starting node */
    // vector_node<T>* begin() {
    //     return FRONT;
    // }
    //
    // /* Returns a pointer to the ending node */
    // vector_node<T>* end() {
    //     return nullptr;
    // }

    /* Returns a pointer to the starting node */
    iterator begin() {
        return iterator(FRONT);
    }

    /* Returns a pointer to the ending node */
    iterator end() {
        return iterator(nullptr);
    }

    T& at(int index) {
        if(0 <= index && index < SIZE) {
            int idx=0;
            vector_node<T>* nd=FRONT;
            for(int i=1; i<= index; i++) {
                nd = nd->next;
            }
            return nd->val;
        } else {
            cout<<"ERROR: index out of bounds"<<endl;
            exit(0);
        }
    }

    /* Operator overloading of the []*/
    T& operator[] (int index) {
        if(0 <= index && index < SIZE) {
            int idx=0;
            vector_node<T>* nd=FRONT;
            for(int i=1; i<= index; i++) {
                nd = nd->next;
            }
            return nd->val;
        } else {
            cout<<"ERROR: index out of bounds"<<endl;
            exit(0);
        }
    }

    /* Returns a reference to the value starting node */
    T &front() {
        return FRONT->val;
    }

    /* Returns a reference to the back node of tht list */
    T &back() {
        return BACK->val;
    }
};

// ostream& operator<<(std::ostream& ostr, Vector<int>& list)
// {
//     for(vector_node<int>* nd = list.begin(); nd!=list.end(); nd = nd->next) {
//         ostr<<nd->val<<" ";
//     }
//     return ostr;
// }

ostream& operator<<(std::ostream& ostr, Vector<int>& list)
{
    for(Vector<int>::iterator itr = list.begin(); itr!=list.end(); ++itr) {
        ostr<<*itr<<" ";
    }
    return ostr;
}


#endif // VECTOR_H


/* TEST-BENCH*/
int main() {
    Vector<int> v;

    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}
    v.push_back(20);
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}
    v.push_back(40);
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}
    v.push_front(89);
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}
    v.push_front(70);
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}
    v.insert(55 , 2);
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    for(int i=0; i<5; i++) {
        v.push_back(i*2);
        v.push_front(-1*i);
    }

    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    cout<<"Front Val: "<<v.front()<<endl;
    cout<<"Back Val: "<<v.back()<<endl;
    cout<<"V[3] : "<<v[3]<<endl;
    cout<<"V[5]: "<<v[5]<<endl;
    cout<<"V[9]: "<<v[9]<<endl;
    cout<<"V[0]: "<<v[0]<<endl;
    cout<<"v.size(): "<<v.size()<<endl;
    cout<<"V[v.size()-1]: "<<v[v.size()-1]<<endl;


    v.pop_back();
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    v.pop_back();
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    v.pop_front();
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    v.pop_front();
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    cout<<"Erase : idx 2"<<endl;
    v.erase(2);
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    cout<<"Erase : idx 0"<<endl;
    v.erase(0);
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    cout<<"Erase : idx size-1"<<endl;
    v.erase(v.size()-1);
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}

    v.clear();
    cout<<"Size : "<<v.size()<<endl;
    if(!v.empty()) {cout<<v<<endl;} else {cout<<"EMPTY"<<endl;}


    return 0;
}
