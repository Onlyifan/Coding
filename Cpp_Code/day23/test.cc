#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


// typedef int (*pFunc)( );
using pFunc = int (*)( );

int ff( ) {
    return 1;
}

int main(void) {
    pFunc x = ff;

    return 0;
}
