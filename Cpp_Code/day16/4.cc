#include <iostream>
#include <string.h>
using std::cout;
using std::endl;


class String {
  public:
    String(const char *str)
        : _str(new char[1 + strlen(str)]( )) {
        strcpy(_str, str);

        cout << "String(const char *str)" << endl;
    }

    ~String( ) {
        if (_str) {
            delete[] _str;
            _str = nullptr;
            cout << "true ";
        }

        cout << "~String()" << endl;
    }

    String(const String &rhs)
        : _str(new char[1 + strlen(rhs._str)]( )) {
        strcpy(_str, rhs._str);
        cout << "finish String(const String &rhs)" << endl;
    }

    String(String &&rhs)
        : _str(rhs._str) {
        rhs._str = nullptr;
        cout << "finish String(String &&rhs)" << endl;
    }

    String &operator=(const String &rhs) {
        if (this != &rhs) {
            delete[] _str;
            _str = new char[1 + strlen(rhs._str)]( );
            strcpy(_str, rhs._str);
        }
        cout << "finish String &operator=(const String &rhs)" << endl;

        return *this;
    }

    String &operator=(String &&rhs) {
        if (this != &rhs) {
            delete[] _str;
            _str = rhs._str;
            rhs._str = nullptr;
        }

        cout << "String &operator=(String &&rhs)" << endl;

        return *this;
    }


  private:
    char *_str;
};


int main(void) {

    String &&p1 = String("abcd");
    cout << &p1 << endl;
    const String &p2 = String("1234");
    cout << &p2 << endl;

    String str1 = "abc";
    String str2("123");
    str2 = str1;
    str2 = String("tmp");


    return 0;
}
