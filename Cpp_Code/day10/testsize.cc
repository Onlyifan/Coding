#include <iostream>
using std::cout;
using std::endl;


class A {

    static char a;
    char b;
};


int main(void) {
    cout << sizeof(A) << endl;

    return 0;
}
