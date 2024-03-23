#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class A {

  public:
    A(long a)
        : _a(a) {}

    long _a;
};

class B : public A {
  public:
    B(long a, long b)
        : A(a)
        , _b(b) {}

    // B &operator=(const B &rhs) = default;

    void print( ) {
        cout << _a << _b << endl;
    }


  private:
    long _b;
};


int main(void) {
    B b1(1, 2);
    B b2(3, 6);
    b1.print( );
    b2.print( );
    b1 = b2;

    b1.print( );

    return 0;
}
