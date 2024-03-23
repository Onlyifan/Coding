#include <iostream>
using namespace std;


void log(const char *msg, int line = __LINE__) {

    cout << msg << line << __LINE__ << endl;
}


void test(const char *msg) {
    log(msg);
}


int main( ) {

    const char *p = "abc";

    log(p);


    return 0;
}

