#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r);
 
// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }
 
 
/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
}
 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
} 

int main() {
    char filename[50];
    printf("Input File Name to Sort: ");
    scanf("%[^\n]s" , filename);
    FILE *fptr1 , *fptr2 , *fptr3;
    FILE* I_O_FILE[2];
    
    I_O_FILE[0] = fopen(filename , "rwb");
    I_O_FILE[1] = fopen("sorted.dat" , "rwb");
    
    long long int cycle=0;
    
    
    while(1)    
        if(inputFile) {
            
            
            int input_file_idx = (cycle%2);
            int output_file_idx = (cycle+1)%2;
            
            FILE *input_file = I_O_FILE[input_file_idx];
            FILE *output_file = I_O_FILE[output_file_idx];
                
            // declare sorted size part
            int sorted_size1 = 1 , sorted_size2 = 1;
            int a , b , itr=0;
            rewind(input_file);
            
            // at the beginning of each prime iteration all the file pointer will be at 0
            while() {
            
            
                fptr2 = fptr1 = input_file;
                itr = 0;
                
                
                // seek at the current position 
                while() {
                    fseek(fptr1 , itr)
                    itr++;
                }
                
                // if fseek is possible for the fptr1 : file has not reached at end
                if(fseek(fptr1 , sorted_size1*sizeof(long long int) , SEEK_CUR))
                // move fptr2 to the beginning of the next part
                fseek(fptr2 , sorted_size2*sizeof(long long int) , SEEK_CUR))
            }    
        }
    
    fclose(input_file);    
    return 0;
}