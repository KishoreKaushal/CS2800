#include<iostream>
#include<fstream>

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
    char file_name[2][50];
    cout<<"Input File: ";   cin.getline(file_name[0], 48);
    cout<<"Output File: "; cin.getline(file_name[1], 48);
    cout<<"You entered:-\nInput File Name : "<<file_name[0]<<"\nOutput File Name: "<<file_name[1]<<endl;

    cout<<"Your input file contains:"<<endl;
    ifstream in_file ;
    in_file.open(file_name[0] , ios::binary|ios::in);
    int num , max_read=10;

    while(in_file.read((char*)&num , sizeof(int)) && max_read--) {
        cout<<num<<endl;
    }

    in_file.seekg(0,in_file.end);
    int length = in_file.tellg();
    cout<<"Size of the file: "<<length<<endl;
    in_file.close();

    int total_int = length/sizeof(int);
    unsigned int total_steps = log2_floor(next_power_of_two(length));
    cout<<"Total Steps: "<< total_steps <<endl;

    int r_num , l_num;
    unsigned int curr_size=0;
    // sorting starts here
    for(unsigned int cycle=0; cycle<total_steps; cycle++) {
        int in_idx = cycle%2;       // input file stream index
        int out_idx = (cycle+1)%2;  // input file

        ifstream in_file(file_name[in_idx], ios::binary|ios::in);
        ofstream out_file(file_name[out_idx], ios::binary|ios::out);

        curr_size = (curr_size<<1) + (curr_size==0); // current size of the sub-array

        if()

        in_file.close();
        out_file.close();
    }


    return 0;
}
