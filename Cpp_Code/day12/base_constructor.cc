#include <iostream>
using std::cout;
using std::endl;

class A {
  public:
    void print( ) {
        cout << "basse";
    }
};


class B : public A {
  public:
};

struct C : B {};


int main(void) {
    C qq;
    qq.print( );
    qq.A::print( );
    qq.B::A::print( );


    return 0;
}
