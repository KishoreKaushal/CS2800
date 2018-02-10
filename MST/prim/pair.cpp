#include<iostream>
using namespace std;
/* Currently used for the purpose of storing the node with distance information in the heap*/
template <typename T1 , typename T2>
struct Pair {
    T1 first;   // key value (in this context the distance from the source)
    T2 second;  // main value (in this context the node number )

    Pair(T1 fst, T2 sec): first{fst} , second{sec} {}
    Pair(const Pair<T1, T2> &P){
        first = P.first;
        second = P.second;
    }
    Pair(){}

    void operator=(const Pair<T1, T2> &P) {
        first = P.first;
        second = P.second;
    }

    void operator=(const T1 &fst) {
        first = fst;
    }

    bool operator== (const Pair<T1, T2> &P) {
        return (first == P.first);
    }

    bool operator!= (const Pair<T1, T2> &P) {
        return (first != P.first);
    }

    bool operator< (const Pair<T1, T2> &P) {
        return (first < P.first);
    }
    bool operator> (const Pair<T1, T2> &P) {
        return (first > P.first);
    }

};

ostream& operator<<(std::ostream& ostr, const Pair<int,int> &P)
{
    ostr<<P.first<<" "<<P.second<<endl;
    return ostr;
}


int main(int argc, char const *argv[]) {
    /* code */
    Pair<int, int> p1(10, 20);
    Pair<int, int> p2(p1);
    Pair<int, int> p3(80 , 30);
    Pair<int, int> p4(80 , 80);
    Pair<int, int> p5(20 , 30);
    cout<<p1<<p2;
    // cout<<(p1!=p2)<<endl;
    // cout<<(p1<p2)<<endl;
    // cout<<(p1>p2)<<endl;
    // cout<<(p1<p3)<<endl;
    // cout<<(p1>p3)<<endl;
    p2 = p5 ;
    cout<<p2<<endl;


    return 0;
}
