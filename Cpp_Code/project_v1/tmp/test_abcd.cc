#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class A {
  public:
    virtual void a( ) {
        cout << "A::a()" << endl;
    }
    virtual void b( ) {
        cout << "A::b()" << endl;
    }
    virtual void c( ) {
        cout << "A::c()" << endl;
    }
};

class B {
  public:
    virtual void a( ) {
        cout << "B::a()" << endl;
    }
    virtual void b( ) {
        cout << "B::b()" << endl;
    }
    void c( ) {
        cout << "B::c()" << endl;
    }
    void d( ) {
        cout << "B::d()" << endl;
    }
};

class C : public A, public B {
  public:
    virtual void a( ) {
        cout << "C::a()" << endl;
    }
    void c( ) {
        cout << "C::c()" << endl;
    }
    void d( ) {
        cout << "C::d()" << endl;
    }
};

class D : public C {
  public:
    void c( ) {
        cout << "D::c()" << endl;
    }
};


void test0( ) {
    C c;
    c.a( );
    c.b( );
    c.c( );
    c.d( );

    cout << endl;
    A *pa = &c;
    pa->a( );
    pa->b( );
    pa->c( );
    pa->d( );

    cout << endl;
    B *pb = &c;
    pb->a( );
    pb->b( );
    pb->c( );
    pb->d( );


    cout << endl;
    C *pc = &c;
    pc->a( );
    pc->b( );
    pc->c( );
    pc->d( );
}
int main(void) {
    test0( );

    return 0;
}
