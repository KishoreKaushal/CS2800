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


int main(int argc, char const *argv[]) {

    return 0;
}
