#include <iostream>
using std::cout;
using std::endl;


void outputOppositeNum(int num = 114) {
    cout << -num << endl;
}

void outputDouble(int num) {
    cout << 2 * num << endl;
}

void outputTriple(int num) {
    cout << 3 * num << endl;
}

void testFunctionObject( ) {
    void (*pfunc1)(int);
    void (*pfunc2)(int) = outputOppositeNum;
    pfunc1 = pfunc2;
    pfunc2 = &outputDouble;
    void (*pfunc3)(int) = &outputTriple;
    pfunc1(10);
    // pfunc1(); // ERROR
    outputOppositeNum( );
    (*pfunc2)(20);
    (*pfunc3)(30);
}

typedef void (*Function)(int);

void testTypedefFunction( ) {
    Function pfunc1;
    Function pfunc2 = outputOppositeNum;
    pfunc1 = pfunc2;
    pfunc2 = &outputDouble;
    Function pfunc3 = &outputTriple;
    pfunc1(10);
    // pfunc1( ); // ERROR
    outputOppositeNum( );
    (*pfunc2)(20);
    (*pfunc3)(30);
}


class ClassF {
  public:
    void outputOppositeNum(int num = 114) {
        cout << -num << endl;
        cout << "exec time:" << ++_count << endl;
    }

    void outputDouble(int num) {
        cout << 2 * num << endl;
        cout << "exec time:" << ++_count << endl;
    }

    void outputTriple(int num) {
        cout << 3 * num << endl;
        cout << "exec time:" << ++_count << endl;
    }

    ClassF( )
        : _count(0) {}

  private:
    int _count;
};

void testMemberFunction( ) {
    void (ClassF::*pfunc1)(int);
    void (ClassF::*pfunc2)(int) = &ClassF::outputOppositeNum;
    pfunc1 = pfunc2;
    pfunc2 = &ClassF::outputDouble;
    void (ClassF::*pfunc3)(int) = &ClassF::outputTriple;

    ClassF f1;

    (f1.*pfunc1)(10);
    //(f1.*pfunc1)();//ERROR
    f1.outputOppositeNum( );
    (f1.*pfunc2)(20);
    (f1.*pfunc3)(30);
}

typedef void (ClassF::*MemberFunction)(int);

void testHeapMemberFunction( ) {

    MemberFunction pfunc1;
    MemberFunction pfunc2 = &ClassF::outputOppositeNum;
    pfunc1 = pfunc2;
    pfunc2 = &ClassF::outputDouble;
    MemberFunction pfunc3 = &ClassF::outputTriple;

    ClassF *f1 = new ClassF( );

    (f1->*pfunc1)(10);
    //(f1->*pfunc1)();//ERROR
    f1->outputOppositeNum( );
    (f1->*pfunc2)(20);
    ((*f1).*pfunc3)(30);
    delete f1;
}


int main(void) {
    testFunctionObject( );

    cout << endl;
    testTypedefFunction( );

    cout << endl;
    testMemberFunction( );
    cout << endl;

    testHeapMemberFunction( );
    return 0;
}
