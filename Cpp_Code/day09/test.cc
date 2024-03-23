#include <iostream>
using std::cout;
using std::endl;

const int &func( ) {

    static int a;


    return a;
}


int main(void) {


    const int &a = func( );

    a++;
    return 0;
}
