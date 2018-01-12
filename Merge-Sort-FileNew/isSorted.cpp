#include<iostream>
using namespace std;
int main() {
    int num1=-1 , num2 , count_cin=0;
    cin>>num2;
    while(!cin.eof()) {
        count_cin++;        
        if(num2<num1) {
            cout<<"Not Sorted"<<endl;
        }
        num1= num2;
        cin>>num2;
    }
    cout<<"No. of bytes: "<<sizeof(int)*count_cin<<endl;
    cout<<"Sorted"<<endl;
    return 0;
}
