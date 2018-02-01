/********************************************************/
/*	Name 		:	Kaushal Kishore						*/
/*	RollNo		:	111601008							*/
/*	FileName	:	heapsort							*/
/********************************************************/


#include<iostream>
#include<climits>


typedef unsigned int uint;
using namespace std;

#define MAXSIZE (200)

#ifndef MINHEAP
#define MINHEAP

#define PARENT(i) ((int)((i-1)/2))
#define LEFT(i) ((int)(2*i + 1 ))
#define RIGHT(i) ((int)(2*i + 2 ))

#define COUNT (10)
//
// // Function to print binary tree in 2D
// // It does reverse inorder traversal
// void print2DUtil(int arr[] ,uint size, uint root, int space){
//     // Base case
//     if (size <= root)
//     return;
//     // Increase distance between levels
//     space += COUNT;
//     // Process right child first
//     print2DUtil(arr , size , RIGHT(root), space);
//     // Print current node after space
//     // count
//     printf("\n");
//     for (int i = COUNT; i < space; i++)
//     printf(" ");
//     printf("%d\n", arr[root]);
//
//     // Process left child
//     print2DUtil(arr , size, LEFT(root), space);
// }
//
// // Wrapper over print2DUtil()
// void print2D(uint root ,int arr[] ,  uint size){
//     // Pass initial space count as 0
//     print2DUtil(arr , size , root, 0);
// }

class min_heap {
public:

    Pair H[MAXSIZE]; // heap array
    int size;       // heap size

    min_heap(): size{0} {}


    /* returns the minimum element present in the heap : the most prior element in the heap*/
    int extract_min(){
        if(size>0){
            Pair min = H[0];
            H[0] = H[--size];
            min_heapify(0);
            return min.second;
        }
        cout<<"ERROR: Heap Underflow"<<endl;
        return INT_MIN;
    }

    /*Returns true if the insertion is successful*/
    bool insert(Pair data) {
        if(size<MAXSIZE){
            H[size] = data;
            int i = size;
            Pair temp;
            while(i!=0 && H[PARENT(i)]>H[i]) {
                temp = H[i];
                H[i] = H[PARENT(i)];
                H[PARENT(i)] = temp;
                i = PARENT(i);
            }
            ++size;
            return true;
        }
        return false;
    }

    /*Function to maintain the heap property of the data structure*/
    void min_heapify(int idx) {
        int smallest = idx;
        if(LEFT(idx)<size && H[LEFT(idx)] < H[smallest])
            smallest = LEFT(idx);
        if(RIGHT(idx)<size && H[RIGHT(idx)] < H[smallest])
            smallest = RIGHT(idx);
        // swap the smallest with the idx
        if(smallest != idx) {
            Pair temp = H[idx];
            H[idx] = H[smallest];
            H[smallest] = temp;
            min_heapify(smallest);
        }
    }

    /*To increase the priority of a certain element at a certain index*/
    void decrease_key(int idx , int new_key) {
        if(new_key < H[idx]){
            H[idx] = new_key;
            min_heapify(idx);
        }
        else cout<<"Attempt to increase the key value using decrease_key()."<<endl;
    }

    /* sets the size of teh heap to zero : which in priciple clears the heap*/
    void clear() {
        size = 0;
    }

    /* Print the heap tree in a pretty way on the terminal */
    void print_heap_min(){
        print2D(0 , H ,  size);
        cout<<endl;
    }
};

/* Build the heap from the array */
void build_heap(min_heap &heap) {
    int n=heap.size;
    for(int i=n/2; i>=0; --i) {
        heap.min_heapify(i);
    }
    cout<<"Heap Becomes:"<<endl;
    heap.print_heap_min();
}

/* Heapsort */
void heapsort(min_heap &heap) {
    cout<<endl<<"Heapsort: ";
    while(heap.size!=0) {
        cout<<heap.extract_min()<<" ";
    }
    cout<<endl<<endl;
}

#endif

// /* Menu list */
// void display_list() {
//     cout<<"1.) Build a heap from an array. "<<endl;
//     cout<<"2.) Insert an element. "<<endl;
//     cout<<"3.) Delete an element. "<<endl;
//     cout<<"4.) Heapsort and Display It."<<endl;
//     cout<<"5.) Display the Heap Tree. "<<endl;
//     cout<<"6.) Insert many elements. "<<endl;
//     cout<<"<0> Exit"<<endl;
//     cout<<"Option [1-5]: ";
// }
//
// /*For case 1*/
// void input_data(min_heap &heap) {
//     int n;
//     cout<<"Enter the number(<100) of the elements in the heap: ";
//     cin>>n;
//     cout<<"Enter the elements: "<<endl;
//     heap.size = 0;
//     for(int i=0; i<n; ++i) {
//         cin>>heap.H[i];
//         ++heap.size;
//     }
//     build_heap(heap);
// }
//
// /* For case 6*/
// void insert_many_elements(min_heap &heap) {
//     uint n;
//     int data;
//     cout<<"Number of the elements to insert (< "<<MAXSIZE - heap.size <<"): ";
//     cin>>n;
//     cout<<"Enter the elements: "<<endl;
//     for (uint i=0; i<n; ++i) {
//         cin>>data;
//         if(heap.insert(data)) {
//             cout<<"Element successfully inserted."<<endl;
//         } else cout<<"Failed to insert an element"<<endl;
//     }
//     cout<<"New Heap : "<<endl;
//     heap.print_heap_min();
// }
//
// /* For case 2 */
// void insert_into_heap(min_heap &heap) {
//     int n;
//     cout<<"Enter the element to insert into the heap: ";
//     cin>>n;
//     if(heap.insert(n)) {
//         cout<<"Element successfully inserted."<<endl;
//         cout<<"New Heap : "<<endl;
//         heap.print_heap_min();
//     } else cout<<"Failed to insert an element"<<endl;
// }

/* For case 3 */
// void delete_from_heap(min_heap &heap) {
//     int n = heap.extract_min();
//     if(n!=INT_MIN) {
//         cout<<"Element extracted from heap: "<<n<<endl;
//         cout<<"New Heap : "<<endl;
//         heap.print_heap_min();
//     }
// }

// int main(int argc, char const *argv[]) {
//     min_heap heap;  // heap declaration
//     int op=1;       // operation selection
//
//
//     while(op!=0){
//         display_list(); // display menu
//         cin>>op;
//         switch(op) {
//             case 0: exit(0);
//             break;
//             case 1:input_data(heap);
//             break;
//             case 2:insert_into_heap(heap);
//             break;
//             case 3:delete_from_heap(heap);
//             break;
//             case 4:heapsort(heap);
//             break;
//             case 5:heap.print_heap_min();
//             break;
//             case 6: insert_many_elements(heap);
//             break;
//             default:cout<<"Wrong choice.. "<<endl;
//             break;
//         }
//     }
//     return 0;
// }
