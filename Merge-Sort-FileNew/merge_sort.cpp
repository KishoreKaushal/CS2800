#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;

unsigned int next_power_of_two(unsigned int v) {
    // compute the next highest power of 2 of 32-bit v
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

int log2_floor (int x){
    int res = -1;
    while (x) { res++ ; x = x >> 1; }
    return res;
}

int main() {
    bool sorted=false;
    char file_name[2][50];
    char sorted_fname[50];
    printf("Input File Name to Sort: ");
    scanf("%[^\n]s" , file_name[0]);
    cout<<endl;
    printf("OutFileName: ");
    scanf(" %[^\n]s" , file_name[1]);


    FILE *fptr_left , *fptr_right , *fptr_out;

    long long int cycle=0 , curr_size=0;
    int num, l_num , r_num;
    int r_count , l_count ;

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
            fseek(fptr_right , curr_size*sizeof(int) , SEEK_CUR);
        }

        // int sub_div_count = 0;
        bool merge_cycle = true , reof=false , leof=false;
        // cout<<"Cycle No.: "<<cycle<<endl;
        /* merging of the array start here */
        while(merge_cycle && !feof(fptr_right) && !feof(fptr_left)) {
            // cout<<"LINE: "<<__LINE__<<endl;
            cout<<"Cycle No.: "<<cycle<<endl;
            r_count = l_count = curr_size;

            while(r_count >0 && l_count>0
                && fread(&r_num , sizeof(int) , 1 , fptr_right)
                && fread(&l_num , sizeof(int) , 1 , fptr_left)
            ) {
                cout<<l_num<<" "<<r_num<<endl;
                if(l_num <= r_num ){
                    cout<<l_num<<" "<<endl;
                    fwrite(&l_num , sizeof(int ) , 1 ,fptr_out);
                    fseek(fptr_right , -sizeof(int), SEEK_CUR);
                    l_count--;
                } else {
                    cout<<r_num<<" "<<endl;
                    fwrite(&r_num , sizeof(int) , 1 , fptr_out);
                    fseek(fptr_left , -sizeof(int) , SEEK_CUR);
                    r_count--;
                }
            }
            // cout<<"LINE: "<<__LINE__<<" "<<l_count<<" "<<r_count<<" "<<l_num<<" "<<r_num<<endl;
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
                while(fread(&l_num , sizeof(int) , 1, fptr_left)) {
                    fwrite(&l_num , sizeof(int) , 1 , fptr_out);
                }
            }

            // if(!feof(fptr_right) && r_count==0) {
            //     cout<<"LINE: "<<__LINE__<<" "<<r_count<<" "<<l_count<<endl;
            //     while(l_count > 0 && fread(&l_num, sizeof(int) , 1 , fptr_left)) {
            //         fwrite(&l_num , sizeof(int) , 1, fptr_out);
            //         cout<<l_num<<" "<<endl;
            //         l_count--;
            //     }
            // } else if(feof(fptr_right)&&!feof(fptr_left)) {
            //     cout<<"LINE: "<<__LINE__<<endl;
            //     while(fread(&l_num, sizeof(int) , 1 , fptr_left)) {
            //         fwrite(&l_num , sizeof(int) , 1, fptr_out);
            //         cout<<l_num<<" "<<endl;
            //     }
            //     break;
            // } else if(l_count == 0) {
            //     cout<<"LINE: "<<__LINE__<<endl;
            //     while(r_count > 0 && fread(&r_num , sizeof(int) , 1 , fptr_right)) {
            //         fwrite(&r_num, sizeof(int) , 1 , fptr_out);
            //         cout<<r_num<<" "<<endl;
            //         r_count--;
            //     }
            // }

            if(feof(fptr_right) && feof(fptr_left)) break;

            // cout<<ftell(fptr_left)<<" "<<ftell(fptr_right)<<endl;

            fseek(fptr_left , curr_size*sizeof(int) , SEEK_CUR);
            fseek(fptr_right, curr_size*sizeof(int), SEEK_CUR);

            // cout<<ftell(fptr_left)<<" "<<ftell(fptr_right)<<endl;
            // break;
            // ++sub_div_count;
            //
            // if(0!=fseek(fptr_left , 2*curr_size*sizeof(int) , SEEK_CUR)||feof(fptr_left)) {
            //     // can't place fptr_left pointer to the desired location :
            //     // the file is complete for the processing
            //     merge_cycle = false ;
            //     break;
            // } else if(0!=fseek(fptr_right, 2*curr_size*sizeof(int), SEEK_CUR)||feof(fptr_right)) {
            //     // can't place fptr_right pointer : can't place the right pointer in the file
            //     // only the fptr_left is placed in the file
            //     // since its already sorted just dump it into the file
            //     while(fread(&num , sizeof(int) , 1 ,fptr_left)) {
            //         fwrite (&num, sizeof(int), 1, fptr_out);
            //     }
            //     merge_cycle = false;
            //     break;
            // }
        }
        // cout<<"Iteraton Val: "<<itr<<endl;
        ++cycle;

        fclose(fptr_right);
        fclose(fptr_left);
        fclose(fptr_out);

        FILE *fptr_in = fopen(file_name[out_idx] , "rb");
        cout<<"Out file after this iteration: ";
        while(fread(&num, sizeof(int), 1, fptr_in)){
           cout<<num<<" ";
        }
        cout<<endl;
        fclose(fptr_in);


        // break;
    }

    /* Converting to human readable format */

    // FILE *fptr_in = fopen(sorted_fname , "r");
    //
    // while(fread(&num, sizeof(int), 1, fptr_in)){
    //    cout<<num<<" ";
    // }
    //
    // fclose(fptr_in);

    return 0;
}
