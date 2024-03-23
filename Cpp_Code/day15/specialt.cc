#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// template <class T1, class T2>
//
// T1 add(T1 x, T2 y) {
//     return x + y;
// }
//
//
//


// template <class T1, class T2> T2 haha(T1 x, T1 y) {
//     return x * y;
// }
template <class T = int, int x = 100> T haha(T y) {
    return x * y;
}

// template <> double haha<int>(int x, int y) {
//     return x - y;
// }


int main(void) {
    // cout << haha(1.2, 1.2);
    int y = 2004;
    cout << haha(1.1);


    return 0;
}
