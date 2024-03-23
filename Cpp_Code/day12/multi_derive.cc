#include <iostream>
using std::cout;
using std::endl;

class A {
  public:
    int print(int a) {
        return 1;
    }
};

class B {
  public:
    void print( ) {}
};

class C : public A, public B {
  public:
};

int main(void) {
    C c;
    A &aa = c;
    aa.print( );

    return 0;
}
