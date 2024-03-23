#include <iostream>
using std::cout;
using std::endl;

int add(int a = 10, double b);
//int add(int a, double b = 20.0) {
//    return 2;
//}
//
int main(void){
    int num = 123;
    int *p = &num;
    int *& hah = p;



    add(0,5);
    return 0;
}

