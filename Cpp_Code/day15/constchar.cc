#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(void) {
    const char *p1 = "abc";
    const char *p2 = "abc";
    const char *p3 = p1 + p2;

    return 0;
}
