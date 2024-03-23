#include <iostream>
#include <string>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

class Base {
  public:
    Base(int num)
        : _pbaseint(new int(num)) {
        cout << "finish Base()" << endl;
    }

    ~Base( ) {
        if (_pbaseint) {
            delete _pbaseint;
            _pbaseint = nullptr;
        }
        cout << "finish ~Base()" << endl;
    }

    void show( ) {
        cout << "Base::show()" << *_pbaseint << endl;
    }

  private:
    int *_pbaseint;
};

class Middle : virtual public Base {
  public:
    Middle(int num1, int num2)
        : Base(num1)
        , _pmiddleint(new int(num2)) {}
    // virtual void show1( ){ };

  private:
    int *_pmiddleint;
};

int main(void) {

    cout << sizeof(Base) << endl;
    cout << sizeof(Middle) << endl;

    Middle mid(11, 22);

    long *pmid = (long *)&mid;
    cout << pmid[0] << endl;
    cout << pmid[1] << endl;
    cout << pmid[2] << endl;
    cout << *(int *)pmid[1] << endl;
    cout << *(int *)pmid[2] << endl;
    cout << endl;
    cout << endl;


    long *vbptr = (long *)pmid[0];

    cout << &Base::show << endl;


    cout << vbptr[0] << endl;
    cout << vbptr[1] << endl;
    cout << vbptr[2] << endl;
    cout << vbptr[3] << endl;
    cout << vbptr[4] << endl;
    cout << vbptr[5] << endl;


    return 0;
}
