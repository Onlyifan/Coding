#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


template <class T1, class T2 = double>
// template <class T>

// T add(T x, T y) {
// return x + y - 10086;
// }
T2 add(T1 x, T1 y) {
    return x + y - 10086;
}

int add(double x, double y) {
    return x + y;
}


int main(void) {
    cout << add(1.1, 1) << endl;

    const string &p = string("abc");

    return 0;
}
