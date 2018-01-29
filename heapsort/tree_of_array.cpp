#include<iostream>
typedef unsigned int uint;
#define PARENT(i) ((int)((i-1)/2))
#define LEFT(i) ((int)(2*i + 1 ))
#define RIGHT(i) ((int)(2*i + 2 ))
#define COUNT 10
using namespace std;

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(int *arr ,uint size, uint root, int space){
    // Base case
    if (size <= root)
        return;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2DUtil(arr , size , RIGHT(root), space);
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", arr[root]);

    // Process left child
    print2DUtil(arr , size, LEFT(root), space);
}

// Wrapper over print2DUtil()
void print2D(uint root ,int *arr ,  uint size){
   // Pass initial space count as 0
   print2DUtil(arr , size , root, 0);
}

int main() {
    int n;
    cin>>n;
    int *arr = new int[n];
    for (int i=0; i<n; i++) {
        cin>>arr[i];
    }
    print2D(0 , arr , n);
    delete [] arr;
    return 0;
}
