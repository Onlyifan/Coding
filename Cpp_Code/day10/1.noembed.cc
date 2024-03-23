#include <iostream>
#include <ostream>
#include <string>
using std::cout;
using std::endl;
using std::ostream;
using std::string;


class AutoRelease;

class Singleton {
  public:
    static Singleton *getInstance(int age = 0, const string &name = "Default") {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton(age, name);
        }

        return _pInstance;
    }

    void setAge(int age) {
        _age = age;
    }

    static void destroyInstance( ) {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    friend ostream &operator<<(ostream &os, const Singleton *instance);

  private:
    Singleton(int age, const string &name)
        : _age(age)
        , _name(name) {}

    ~Singleton( ) = default;
    Singleton(const Singleton &rhs) = delete;

  private:
    int _age;
    string _name;
    static Singleton *_pInstance;
    static AutoRelease _ar;
};


class AutoRelease {
  public:
    ~AutoRelease( ) {
        Singleton::destroyInstance( );
    }
};


Singleton *Singleton::_pInstance = nullptr;
AutoRelease Singleton::_ar{ };


ostream &operator<<(ostream &os, const Singleton *instance) {
    os << "(" << instance->_name << ": " << instance->_age << ")";
    return os;
}


void test( ) {
    cout << Singleton::getInstance( ) << endl;
    Singleton::getInstance( )->setAge(23);
    cout << Singleton::getInstance( ) << endl;
}


int main(void) {


    test( );

    cout << Singleton::getInstance( ) << endl;
    Singleton::destroyInstance( );

    Singleton::getInstance(10, "tom");
    cout << Singleton::getInstance( ) << endl;
    Singleton::destroyInstance( );
    Singleton::destroyInstance( );
    Singleton::destroyInstance( );
    cout << Singleton::getInstance(8, "haha") << endl;


    return 0;
}
