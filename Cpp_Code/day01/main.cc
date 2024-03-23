#include <iostream>
using std::cin;
using std::cout;
using std::endl;


namespace MySpace {
    extern void swap(int &, int &);
}


int main(void){
    int a = 2;
    int b = 4;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    MySpace::swap(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    return 0;
}
