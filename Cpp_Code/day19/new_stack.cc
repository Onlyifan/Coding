#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


class P {
  public:
    P(int x)
        : p(new int(x)) {
        cout << "finish P()" << endl;
    }
    ~P( ) {
        delete p;
        cout << "finish ~P()" << endl;
    }
    P(const P &) = delete;
    void display( ) {
        cout << *p << endl;
    }

  private:
    int *p;
};


int main(void) {
    // char what[3];
    // new (what) "as";
    char what[sizeof(P)];
    P *pp = new (what) P(3);
    pp->display( );

    return 0;
}
