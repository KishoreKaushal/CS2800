#include<iostream>
#define MAXSIZE (100)

#ifndef MINHEAP
#define MINHEAP

#define PARENT(i) ((int)((i-1)/2))
#define LEFT(i) ((int)(2*i + 1 ))
#define RIGHT(i) ((int)(2*i + 2 ))

struct min_heap {
    int &H[];
    int size;

    min_heap(int &arr , int n): H{arr} , size{n} {}

    int extract_min(){
        if(size>0){
            int min = H[0];
            H[0] = H[--size];
            min_heapify(0);
            return min;
        }
        cout<<"ERROR: Heap Underflow"<<endl;
        return INT_MIN;
    }

    void insert(int data) {
        if(size<MAXSIZE){
            H[size] = data;
            int i = size, temp;
            while(i!=0 && H[PARENT(i)]>H[i]) {
                temp = H[i];
                H[i] = H[PARENT(i)];
                H[PARENT(i)] = temp;
                i = PARENT(i);
            }
            ++size;
        }
    }

    void min_heapify(int idx) {
        smallest = idx;
        if(LEFT(idx)<size && H[LEFT(idx)] < H[smallest])
            smallest = LEFT(idx);
        if(RIGHT(idx)<size && H[RIGHT(idx)] < H[smallest])
            smallest = RIGHT(idx);
        // swap the smallest with the idx
        if(smallest != idx) {
            int temp = H[idx];
            H[idx] = H[smallest];
            H[smallest] = temp;
            min_heapify(smallest);
        }
    }

    void increase_priority(int idx , int increment=1) {
        if(increment>=1){
            H[idx]+=increment;
            min_heapify(idx);
        }
        else cout<<"You cannot decrease the priority."<<endl;
    }

    void clear() {
        size = 0;
    }
};

min_heap build_heap_from_array(int &arr[] , int n) {
    min_heap H(arr , n);
    for(int i=n-1; i>=0; --i) {
        H.min_heapify(i);
    }
    return H;
}

void heapsort(min_heap &heap) {
    cout<<"heapsort: ";
    while(heap.size!=0) {
        cout<<heap.extract_min()<<" ";
    }
    cout<<endl;
}

#endif

void display_list() {
    cout<<"1.) Build a heap. "<<endl;
    cout<<"2.) Insert an element. "<<endl;
    cout<<"3.) Delete an element. "<<endl;
    cout<<"4.) Heapsort and Display It."<<endl;
    cout<<"5.) Display the Heap Tree. "<<endl;
    cout<<"<0> Exit"<<endl;
    cout<<"Option [1-5]: ";
}

int main(int argc, char const *argv[]) {
    // 1 build a heap
    // 2 insert an element
    // 3 delete the minimum element

    // 4 heapsort and display
    // 5 display the heap
    int op;
    display_list();
    cin>>op;
    switch(op) {
        case 0: exit(0);
        break;
        case 1:
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        case 5:
        break;
        default:    cout<<"Wrong choice.. "<<endl;
        break;
    }
    return 0;
}
