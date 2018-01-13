#include<iostream>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<ctime>

#define TOTAL_NUM (1000)
#define MAX_VAL (20000)

using namespace std;

int main() {
    char inFname[] = "input.bin";
    //    char readFname[] = "readable.input";
//    char inFname[50];
    int num;
    //cout<<"Input File: ";
    //cin>>inFname;
    FILE *fptr1 = fopen(inFname , "r");
    //FILE *fptr2 = fopen(readFname , "r");

    fseek(fptr1, 0, SEEK_END); // seek to end of file
    unsigned int size = ftell(fptr1); // get current file pointer
    fseek(fptr1, 0, SEEK_SET);
    cout<<"Size of the input.bin file: " <<size<<" bytes"<<endl;
    cout<<"Number of Integers in the file: "<<size/sizeof(int)<<endl;
    // fseek ( fptr1 , 2*sizeof( int) , SEEK_SET );
    // fread(&num , sizeof( int) , 1 ,fptr1);
    // cout<<num<<endl;
    while(fread(&num, sizeof(int), 1, fptr1)){
//       cout<<num<<" ";
    }
    //
    //if(fptr1 && fptr2) {
    //    srand(time(NULL));                  // seed for the random number
    //    for(int i=0; i<TOTAL_NUM; i++) {
    //        num = rand()%MAX_VAL;
    //        cout<<num<<endl;
    //        fwrite (&num, sizeof(long long int), 1, fptr1);
    //        fwrite (&num, sizeof(long long int), 1, fptr2);
    //    }
    //}

    fclose(fptr1);
    //fclose(fptr2);
    return 0;
}
