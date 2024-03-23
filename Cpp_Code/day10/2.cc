#include <iostream>
#include <ostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

typedef int refcount_t;

class CowString {
  private:
    class Typechar {
      public:
        Typechar( )
            : _ch('\0') {}

        Typechar(char ch, std::size_t index, CowString *srcStr)
            : _ch(ch)
            , _index(index)
            , _srcCowStr(srcStr) {}

        // friend ostream &operator<<(ostream &os, const Typechar &Tchar);

        Typechar &operator=(char ch) {
            if (_ch == ch) {
                return *this;
            }

            if (_srcCowStr->viewRefcount( ) == 1) {
                _srcCowStr->_pstr[_index] = ch;
                return *this;
            }
            _srcCowStr->decreaseRefcount( );

            char *newStr = _srcCowStr->initPstr(_srcCowStr->_pstr);
            newStr[_index] = ch;

            // 原字符串计数-1
            _srcCowStr->_pstr = newStr;
            return *this;
        }

        operator char( ) {
            return _ch;
        }

      private:
        char _ch;
        std::size_t _index;
        CowString *_srcCowStr;
    };

  public:
    CowString( )
        : _pstr(initPstr( )) {}
    ~CowString( ) {
        releasePstr( );
    }

    CowString(const char *pstr)
        : _pstr(initPstr(pstr)) {}

    CowString(const CowString &str)
        : _pstr(str._pstr) {
        increaseRefcount( );
    }

    std::size_t size( ) const {
        return strlen(_pstr);
    }

    const char *c_str( ) const {
        return _pstr;
    }

    // 自复制问题
    CowString &operator=(const CowString &rhs) {
        if (this != &rhs) {
            releasePstr( );
            _pstr = rhs._pstr;
            increaseRefcount( );
        }
        return *this;
    }

    Typechar operator[](std::size_t index) {
        if (index < strlen(_pstr)) {
            return Typechar(_pstr[index], index, this);
        }

        static Typechar errorTypeChar{ };
        return errorTypeChar;
    }

    friend ostream &operator<<(ostream &os, const CowString &rhs);
    // friend ostream &operator<<(ostream &os, const CowString::Typechar
    // &Tchar);

  private:
    char *initPstr(const char *pstr = "") {
        char *newStr =
            new char[1 + strlen(pstr) + kRefcountLength]( ) + kRefcountLength;
        *(int *)(newStr - kRefcountLength) = 1;
        strcpy(newStr, pstr);
        return newStr;
    }

    void releasePstr( ) {
        if (viewRefcount( ) == 1) {
            delete[] (_pstr - kRefcountLength);
            _pstr = nullptr;
            return;
        }

        decreaseRefcount( );
    }

    refcount_t viewRefcount( ) {
        return *(int *)(_pstr - kRefcountLength);
    }

    void increaseRefcount( ) {
        ++*(int *)(_pstr - kRefcountLength);
    }

    void decreaseRefcount( ) {
        --*(int *)(_pstr - kRefcountLength);
    }


  private:
    static int kRefcountLength;
    char *_pstr;
};
int CowString::kRefcountLength = sizeof(refcount_t);


ostream &operator<<(ostream &os, const CowString &rhs) {
    os << rhs._pstr;
    return os;
}


// ostream &operator<<(ostream &os, const CowString::Typechar &Tchar) {
//     os << Tchar._ch;
//     return os;
// }

int main(void) {
    

    // CowString str1;
    // CowString str2 = str1;
    // cout << "str1:" << str1 << endl;
    // cout << "str2:" << str2 << endl;

    // cout << "#############" << endl;
    // CowString str3("hello");
    // cout << "str3:" << str3 << endl;
    // CowString str4 = str3;
    // cout << "str3:" << str3 << endl;
    // cout << "str4:" << str4 << endl;

    // cout << "#############" << endl;
    // str1 = str3;
    // cout << "str1:" << str1 << endl;
    // cout << "str2:" << str2 << endl;
    // cout << "str3:" << str3 << endl;
    // cout << "str4:" << str4 << endl;
    CowString str1("hello");
    CowString str2("world");
    str2 = str1;
    cout << str1 << endl;
    cout << str2 << endl;

    str1[0] = 'H';
    cout << str1 << endl;
    cout << str2 << endl;


    return 0;
}
