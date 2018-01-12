#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<ctime>

#define MAX_VAL (5000)
// #define TOTAL_NUM (10)

using namespace std;

int main() {
    char bin_file[] = "input.bin";
    char txt_file[] = "input.txt";
    long long int num;

    FILE *fptr1 = fopen(bin_file , "wb");
    FILE *fptr2 = fopen(txt_file , "w");

    if(fptr1 && fptr2) {
        srand(time(NULL));                  // seed for the random number
        int TOTAL_NUM = rand()%1000;
        for(int i=0; i<TOTAL_NUM; i++) {
            num = rand()%MAX_VAL;
            cout<<num<<endl;
            fwrite (&num, sizeof(int), 1, fptr1);
            fprintf(fptr2 , "%d " , num);
            // fprintf (&num, sizeof(long long int), 1, fptr2);
        }
    }

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
