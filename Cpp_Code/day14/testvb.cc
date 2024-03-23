#include <iostream>
#include <string>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

class Base {
    void show(int a) {}
    void showbase(int a) {}

  private:
    uint64_t _pbaseint = 333;
};


class Base1 : virtual public Base {
  public:
    void show(int num) {
        cout << "Base::show()" << _pbaseint1 << endl;
    }
    void ehhe( ) {}

  private:
    uint64_t _pbaseint1 = 111;
};


class Base2 : virtual public Base {
  public:
    void show2(int num) {
        cout << "Base::show()" << _pbaseint2 << endl;
    }

    virtual void eh1whe( ) {}

  private:
    uint64_t _pbaseint2 = 211;
};


class Middle : public Base1, public Base2 {
  public:
    void showhello(int num) {
        cout << "Middle::show()" << num << endl;
    }

    virtual void show(int num) {}

  private:
    uint64_t _pmiddleint = 222;
};

int main(void) {

    cout << sizeof(Base1) << endl;
    cout << sizeof(Middle) << endl;

    Middle mid;

    long *pmid = reinterpret_cast<long *>(&mid);
    cout << pmid[0] << endl;
    cout << pmid[1] << endl;
    cout << pmid[2] << endl;
    cout << pmid[3] << endl;
    cout << endl;
    cout << endl;


    // long *vbptr = reinterpret_cast<long *>(pmid[0]);
    //
    // cout << vbptr[0] << endl;
    //
    // typedef void (*Function)(int);
    // Function func = (Function)vbptr[0];
    // func(233);
    //
    // cout << vbptr[1] << endl;
    // cout << vbptr[2] << endl;
    // cout << vbptr[3] << endl;
    // cout << vbptr[4] << endl;
    // cout << vbptr[5] << endl;
    // cout << vbptr[6] << endl;
    //

    return 0;
}
