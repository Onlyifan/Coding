#include <iostream>
using std::cout;
using std::endl;

class Base {
  public:
    virtual void show( ) {
        cout << "Base::show()" << endl;
    }
    virtual void print( );
    virtual void display( ) {
        cout << "Base::display()" << endl;
    }

    long base = 11;
};


void Base::print( ) {
    cout << "Base::prin()" << endl;
}

class Middle : public Base {
  public:
    void show( ) {
        cout << "Middle::show()" << endl;
    };
    virtual void midshow( ) {
        cout << "Middle::midshow()" << endl;
    };

    long middle = 22;
};

int main(void) {

    cout << sizeof(Base) << endl;
    cout << sizeof(Middle) << endl;

    Middle mid{ };

    long *pmid = reinterpret_cast<long *>(&mid);

    cout << pmid[1] << endl;
    cout << pmid[2] << endl;
    typedef void (*Func)( );

    long *pfunc = reinterpret_cast<long *>(pmid[0]);

    Func func = (Func)pfunc[0];
    func( );
    func = (Func)pfunc[1];
    func( );
    func = (Func)pfunc[2];
    func( );
    func = (Func)pfunc[3];
    func( );


    return 0;
}
