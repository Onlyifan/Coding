#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


int &&add( ) {
    int a = 1;
    return std::move(a);
}


int main(void) {


    return 0;
}
