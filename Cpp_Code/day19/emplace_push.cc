#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;


class AAA {
  public:
    AAA( ) {
        cout << "AAA()" << endl;
    }

    AAA(int a, const char *p)
        : _a(a)
        , _p(new char[1 + strlen(p)]( )) {
        cout << "AAA(int a, const char *p)" << endl;
    }

    // AAA(const AAA &rhs) = delete;
    AAA(const AAA &rhs)
        : _a(rhs._a)
        , _p(new char[1 + strlen(rhs._p)]) {
        cout << "AAA(const AAA &rhs)" << endl;
    }

    AAA(AAA &&rhs)
        : _a(rhs._a)
        , _p(rhs._p) {
        rhs._p = nullptr;
        cout << "AAA(AAA &&rhs)" << endl;
    }

    ~AAA( ) {
        if (_p) {
            cout << "true ";
            delete[] _p;
        }
        cout << "~AAA( )" << endl;
    }

  private:
    int _a;
    char *_p;
};


int main(void) {
    vector<AAA> vec;

    // vec.reserve(100);
    // vec.emplace_back(1, "abfe");
    // vec.emplace_back( );
    // vec.reserve(100);
    AAA a(123, "abc");
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));
    vec.push_back(AAA(1, "aa"));

    // vec.push_back(std::move(a));
    // vec.push_back(AAA(345, "ss"));
    cout << "--------------" << endl;
    // char arr[sizeof(AAA)];
    // AAA a(1, "abc");
    // AAA *p = new (arr) AAA(a);


    return 0;
}
