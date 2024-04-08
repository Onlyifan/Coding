#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int main(void) {
    int a = 0x11223344;
    int *p = &a;

    int lowAddr = *reinterpret_cast<char *>(p);


    cout << "num = " << std::hex << a << endl;
    cout << "lowAddr = " << std::hex << lowAddr << endl;

    return 0;
}
