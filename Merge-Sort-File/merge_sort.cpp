#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;
//
// * Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
// void merge(int arr[], int l, int m, int r);
//
// // Utility function to find minimum of two integers
// int min(int x, int y) { return (x<y)? x :y; }

//
// /* Iterative mergesort function to sort arr[0...n-1] */
// void mergeSort(int arr[], int n)
// {
//    int curr_size;  // For current size of subarrays to be merged
//                    // curr_size varies from 1 to n/2
//    int left_start; // For picking starting index of left subarray
//                    // to be merged
//
//    // Merge subarrays in bottom up manner.  First merge subarrays of
//    // size 1 to create sorted subarrays of size 2, then merge subarrays
//    // of size 2 to create sorted subarrays of size 4, and so on.
//    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
//    {
//        // Pick starting point of different subarrays of current size
//        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
//        {
//            // Find ending point of left subarray. mid+1 is starting
//            // point of right
//            int mid = left_start + curr_size - 1;
//
//            int right_end = min(left_start + 2*curr_size - 1, n-1);
//
//            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
//            merge(arr, left_start, mid, right_end);
//        }
//    }
// }
//
// /* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
// void merge(int arr[], int l, int m, int r)
// {
//     int i, j, k;
//     int n1 = m - l + 1;
//     int n2 =  r - m;
//
//     /* create temp arrays */
//     int L[n1], R[n2];
//
//     /* Copy data to temp arrays L[] and R[] */
//     for (i = 0; i < n1; i++)
//         L[i] = arr[l + i];
//     for (j = 0; j < n2; j++)
//         R[j] = arr[m + 1+ j];
//
//     /* Merge the temp arrays back into arr[l..r]*/
//     i = 0;
//     j = 0;
//     k = l;
//     while (i < n1 && j < n2)
//     {
//         if (L[i] <= R[j])
//         {
//             arr[k] = L[i];
//             i++;
//         }
//         else
//         {
//             arr[k] = R[j];
//             j++;
//         }
//         k++;
//     }
//
//     /* Copy the remaining elements of L[], if there are any */
//     while (i < n1)
//     {
//         arr[k] = L[i];
//         i++;
//         k++;
//     }
//
//     /* Copy the remaining elements of R[], if there are any */
//     while (j < n2)
//     {
//         arr[k] = R[j];
//         j++;
//         k++;
//     }
// }

int main() {
    bool sorted=false;
    char file_name[2][50];
    char sorted_fname[50];
    printf("Input File Name to Sort: ");
    scanf("%[^\n]s" , file_name[0]);
    cout<<endl;
    printf("OutFileName: ");
    scanf(" %[^\n]s" , file_name[1]);


    FILE *fptr_left , *fptr_right , *fptr_out , *fptr_in;


    long long int cycle=0 , curr_size=0;
    int num, l_num , r_num;
    //fseek(fptr1 , sorted_size1*sizeof(long long int) , SEEK_CUR)

    while(!sorted) {
        int in_idx = cycle%2;       // input file stream index
        int out_idx = (cycle+1)%2;  // input file

        fptr_in = fopen(file_name[in_idx] , "rwb"); // input file stream
        fptr_out = fopen(file_name[out_idx] , "wb");   // output file stream

        if(!fptr_out) {
            cout<<"Out File Not Opening"<<endl;
            cout<<"Infile: "<<file_name[in_idx]<<endl;
            cout<<"Outfile: "<<file_name[out_idx]<<endl;
            break;
        }

        curr_size = (curr_size<<1) + (curr_size==0); // current size of the sub-array
        fptr_right = fptr_left = fptr_in;   // initializing

        if(0 != fseek(fptr_right , curr_size * sizeof(int), SEEK_CUR)) {
            // already sorted : record the outfile name
            strcpy(sorted_fname , file_name[in_idx]);
            sorted = true;
            fclose(fptr_in);
            fclose(fptr_out);
            break;
        }


        int sub_div_count=0;
        bool merge_cycle = true;

        while(merge_cycle) {
            cout<<"In Merge Cycle : cycle : "<<cycle<<endl;
            cout<<"At line: "<<__LINE__<<endl;
            // Assuming the sub-array to be sorted in each step
            if(0 != fseek(fptr_left, 2 * sub_div_count * curr_size * sizeof(int), SEEK_CUR)) {
                // can't place fptr_left pointer : the file is complete processing for this cycle
                merge_cycle = false;
                break;
            } else if(0 != fseek(fptr_right , 2 * sub_div_count * curr_size * sizeof(int), SEEK_CUR)) {
                // can't place fptr_right pointer : can't place the right pointer in the file
                // only the fptr_left is placed in the file
                // since its already sorted just dump it into the file
                while(fread(&num , sizeof(int) , 1 ,fptr_left)) {
                    fwrite (&num, sizeof(int), 1, fptr_out);
                }
                merge_cycle = false;
                break;
            }

            // merging of the file start here
            cout<<"At line: "<<__LINE__<<endl;
            int r_count = curr_size ,  l_count = curr_size;
            while(r_count>0 && l_count>0
                && fread(&l_num , sizeof(int) , 1 , fptr_left)
                && fread(&r_num , sizeof(int) , 1, fptr_right)) {

                if(l_num <= r_num) {
                    cout<<"At line: "<<__LINE__<<endl;
                    // writing the l_num to the file
                    fwrite(&l_num , sizeof(int) , 1 , fptr_out);
                    fseek(fptr_right , -sizeof(int) , SEEK_CUR);
                    l_count--;
                } else {
                    cout<<"At line: "<<__LINE__<<endl;
                    // writing the r_num to the file
                    fwrite(&r_num , sizeof(int) , 1 , fptr_out);
                    fseek(fptr_left , -sizeof(int) , SEEK_CUR);
                    r_count--;
                }
            }

            if(!feof(fptr_right)||r_count==0) {
                cout<<"At line: "<<__LINE__<<endl;
                //  all the right sub-array is dumped into the output file
                // dump all the left sub-array into the output file
                while(l_count > 0 && fread(&l_num ,sizeof(int) , 1 , fptr_left)) {
                    fwrite(&l_num , sizeof(int) , 1 , fptr_out);
                    l_count--;
                }

            } else if(l_count == 0) {
                cout<<"At line: "<<__LINE__<<endl;
                // all the left sub-array is dumped into the output file
                while(r_count > 0 && fread(&r_num ,sizeof(int) , 1 , fptr_right)) {
                    fwrite(&r_num , sizeof(int) , 1 , fptr_out);
                    r_count--;
                }
            }
            // rhis step is complete
            ++sub_div_count;
        }
        cout<<"At line: "<<__LINE__<<endl;

        cycle++;
        fclose(fptr_in);
        fclose(fptr_out);
    }

    /* Converting to human readable format */

    fptr_in = fopen(sorted_fname , "r");

    while(fread(&num, sizeof(int), 1, fptr_in)){
       cout<<num<<" ";
    }

    fclose(fptr_in);
    return 0;
}
