#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;

int main() {
    char file_name[2][50];
    char sorted_fname[50];

    printf("Input File Name (Binary-Format) to Sort: ");
    scanf("%[^\n]s" , file_name[0]);
    cout<<endl;
    cout<<"Output File Name: output.txt"<<endl;
    strcpy(file_name[1] , "temp.bin");

    long long int cycle=0 , curr_size=0;
    int num, l_num , r_num, r_count , l_count ;
    bool sorted=false;
    FILE *fptr_left , *fptr_right , *fptr_out;

    while(!sorted) {
        int in_idx = cycle%2;       // input file stream index
        int out_idx = (cycle+1)%2;  // input file

        fptr_left = fopen(file_name[in_idx] , "rwb"); // input file stream
        fptr_right = fopen(file_name[in_idx] , "rwb"); // input file stream
        if(!fptr_right || !fptr_left) {
            cout<<"Input file not opening"<<endl;
            fclose(fptr_right);
            fclose(fptr_left);
            exit(0);
        }
        fptr_out = fopen(file_name[out_idx] , "wb");   // output file stream

        curr_size = (curr_size<<1) + (curr_size==0); // current size of the sub-array

        /* Size of the file  */
        fseek(fptr_right, 0, SEEK_END);
        unsigned long long int size_of_file = ftell(fptr_right);
        fseek(fptr_right, 0, SEEK_SET);

        if(size_of_file<=curr_size*sizeof(int)) {
            // already sorted : record the outfile name
            strcpy(sorted_fname , file_name[in_idx]);
            sorted = true;
            fclose(fptr_right);
            fclose(fptr_left);
            fclose(fptr_out);
            break;
        } else {
            /* Initiliazing the fptr_right */
            fseek(fptr_right , curr_size*sizeof(int) , SEEK_CUR);
        }

        bool merge_cycle = true ;

        /* merging of the array start here */
        while(merge_cycle && !feof(fptr_right) && !feof(fptr_left)) {
            r_count = l_count = curr_size; // size of the sub-array

            while(r_count >0 && l_count>0
                && fread(&r_num , sizeof(int) , 1 , fptr_right)
                && fread(&l_num , sizeof(int) , 1 , fptr_left)
            ) {
                // cout<<l_num<<" "<<r_num<<endl;
                if(l_num <= r_num ){
                    // cout<<l_num<<" "<<endl;
                    fwrite(&l_num , sizeof(int ) , 1 ,fptr_out);
                    fseek(fptr_right , -sizeof(int), SEEK_CUR);
                    l_count--;
                } else {
                    // cout<<r_num<<" "<<endl;
                    fwrite(&r_num , sizeof(int) , 1 , fptr_out);
                    fseek(fptr_left , -sizeof(int) , SEEK_CUR);
                    r_count--;
                }
            }

            if(feof(fptr_left) && feof(fptr_right)) break;

            if(r_count==0 && l_count!=0) {
                while(l_count>0 && fread(&l_num , sizeof(int) , 1, fptr_left)) {
                    fwrite(&l_num , sizeof(int) , 1 , fptr_out);
                    l_count--;
                }
            } else if(l_count==0) {
                while(r_count>0&& fread(&r_num , sizeof(int) , 1 , fptr_right)){
                    fwrite(&r_num , sizeof(int) , 1, fptr_out);
                    r_count--;
                }
            } else if(feof(fptr_left)) {
                break;
            } else if(feof(fptr_right)) {
                while(l_count>0 && fread(&l_num , sizeof(int) , 1, fptr_left)) {
                    fwrite(&l_num , sizeof(int) , 1 , fptr_out);
                    l_count--;
                }
            }

            if(feof(fptr_right) && feof(fptr_left)) break;

            fseek(fptr_left , curr_size*sizeof(int) , SEEK_CUR);
            fseek(fptr_right, curr_size*sizeof(int), SEEK_CUR);
            if(size_of_file<=ftell(fptr_left)) break;
        }
        ++cycle;

        /* Closing all the file pointer */
        fclose(fptr_right);
        fclose(fptr_left);
        fclose(fptr_out);
    }

    /* Converting to human readable format */

    FILE *fptr_in = fopen(sorted_fname , "rb");
    FILE *sorted_data = fopen("output.txt" , "w");

    while(fread(&num, sizeof(int), 1, fptr_in)){
       // cout<<num<<" ";
       fprintf(sorted_data, "%d\n", num);
    }

    fclose(fptr_in);
    fclose(sorted_data);
    return 0;
}
