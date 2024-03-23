#include <iostream>
using std::cout;
using std::endl;


class A {
  public:
    class B {
        double a;
        int b;
    };

  private:
    B b;
    int a;
};


int main(void) {
    cout << sizeof(A) << endl;
    cout << sizeof(A::B) << endl;

    return 0;
}
