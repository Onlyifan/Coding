
#include <iostream>

int a = 10;

namespace  {
    int a = 20;
}

int main(void) {

    std::cout << ::a;


}
