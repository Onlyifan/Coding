#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
using std::cout;
using std::endl;

class String {
  public:
    String( );
    String(const char *);
    String(const String &);
    ~String( );
    String &operator=(const String &);
    String &operator=(const char *);

    String &operator+=(const String &);
    String &operator+=(const char *);

    char &operator[](std::size_t index);
    const char &operator[](std::size_t index) const;

    std::size_t size( ) const;
    // const char *c_str( ) const;
    const char *c_str( );

    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    // friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

  private:
    char *_pstr;
};

String::String( )
    : _pstr(new char[1]( )) {
    // cout << "finish String()" << endl;
}

String::String(const char *str)
    : _pstr(new char[1 + strlen(str)]( )) {
    strcpy(_pstr, str);
    // cout << "finish String(const char *str)" << endl;
}

String::String(const String &rhs)
    : _pstr(new char[1 + strlen(rhs._pstr)]) {
    strcpy(_pstr, rhs._pstr);
    // cout << "finish String(const String &rhs)" << endl;
}

String::~String( ) {
    if (_pstr) {
        delete[] _pstr;
        cout << "Truely ";
    }
    cout << "finish ~String()" << endl;
}

String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        delete[] _pstr;
        _pstr = new char[1 + rhs.size( )]( );
        strcpy(_pstr, rhs._pstr);
        // cout << "True ";
    }

    // cout << "finish operator=(const String &rhs)" << endl;
    return *this;
}
String &String::operator=(const char *str) {

    if (strcmp(_pstr, str) != 0) {
        delete[] _pstr;
        _pstr = new char[1 + strlen(str)]( );
        strcpy(_pstr, str);
        // cout << "True ";
    }
    // cout << "finish operator=(const char *str)" << endl;
    return *this;
}

String &String::operator+=(const String &rhs) {
    std::size_t oldSize = strlen(_pstr);
    char *newStr = new char[1 + oldSize + strlen(rhs._pstr)]( );
    memcpy(newStr, _pstr, oldSize);
    strcat(newStr, rhs._pstr);
    delete[] _pstr;
    _pstr = newStr;

    // cout << "finish operator+=(const String &rhs)" << endl;
    return *this;
}

String &String::operator+=(const char *str) {
    std::size_t oldSize = strlen(_pstr);
    char *newStr = new char[1 + oldSize + strlen(str)]( );
    memcpy(newStr, _pstr, oldSize);
    strcat(newStr, str);
    delete[] _pstr;
    _pstr = newStr;

    // cout << "finish operator+=(const char *str)" << endl;
    return *this;
}

char &String::operator[](std::size_t index) {
    if (index >= strlen(_pstr)) {
        static char errorChar1 = 0;
        // cout << "error finish operator[](size_t index)" << endl;
        return errorChar1;
    }

    // cout << "finish operator[](size_t index)" << endl;
    return _pstr[index];
}

const char &String::operator[](std::size_t index) const {
    if (index >= strlen(_pstr)) {
        static char errorChar2 = 0;
        // cout << "error finish operator[](size_t index) const{}" << endl;
        return errorChar2;
    }

    // cout << "finish operator[](size_t index) const{}" << endl;
    return _pstr[index];
}

std::size_t String::size( ) const {

    // cout << "finish size()" << endl;
    return strlen(_pstr);
}

// const char *String::c_str( ) const {
const char *String::c_str( ) {
    // cout << "finish c_str()" << endl;
    return _pstr;
}

bool operator==(const String &lhs, const String &rhs) {
    // cout << "finish operator==" << endl;
    return !strcmp(lhs._pstr, rhs._pstr);
}

bool operator!=(const String &lhs, const String &rhs) {
    // cout << "finish operator!=" << endl;
    return strcmp(lhs._pstr, rhs._pstr);
}

bool operator<(const String &lhs, const String &rhs) {
    // cout << "finish operator<" << endl;
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String &lhs, const String &rhs) {
    // cout << "finish operator>" << endl;
    return strcmp(lhs._pstr, rhs._pstr) > 0;
}
bool operator<=(const String &lhs, const String &rhs) {
    // cout << "finish operator<=" << endl;
    return strcmp(lhs._pstr, rhs._pstr) <= 0;
}

bool operator>=(const String &lhs, const String &rhs) {
    // cout << "finish operator>=" << endl;
    return strcmp(lhs._pstr, rhs._pstr) >= 0;
}

std::ostream &operator<<(std::ostream &os, const String &s) {
    // os << s._pstr;
    os << s.c_str( );

    // cout << "finish operator<<" << endl;
    return os;
}
std::istream &operator>>(std::istream &is, String &s) {
    //// std::size_t oldSize = strlen(s._pstr);
    // char buf[4096] = {0};
    // is.getline(buf, sizeof(buf), '\n');

    //// char *newStr = new char[1 + oldSize + strlen(buf)]( );
    // char *newStr = new char[1 + strlen(buf)]( );
    //// memcpy(newStr, s._pstr, oldSize);
    //// strcat(newStr, buf);
    // strcpy(newStr, buf);

    // delete[] s._pstr;
    // s._pstr = newStr;

    //// cout << "finish operator>>" << endl;
    // return is;
    if (s._pstr) {
        delete[] s._pstr;
    }

    std::vector<char> buffer;
    while (char ch = is.get( ) != '\n') {
        buffer.push_back(ch);
    }

    s._pstr = new char[1 + buffer.size( )]( );
    strncpy(s._pstr, &buffer[0], buffer.size( ));

    return is;
}

String operator+(const String &lhs, const String &rhs) {
    char *tmpStr = new char[1 + lhs.size( ) + rhs.size( )]( );
    strcpy(tmpStr, lhs.c_str( ));
    strcat(tmpStr, rhs.c_str( ));

    String result(tmpStr);
    delete[] tmpStr;

    // cout << "finish operator+(const String &lhs, const String &rhs)" << endl;
    return result;
}

String operator+(const String &lhs, const char *str) {
    char *tmpStr = new char[1 + lhs.size( ) + strlen(str)]( );
    strcpy(tmpStr, lhs.c_str( ));
    strcat(tmpStr, str);

    String result(tmpStr);
    delete[] tmpStr;

    // cout << "finish operator+(const String &lhs, const char *str)" << endl;
    return result;
}

String operator+(const char *str, const String &rhs) {
    char *tmpStr = new char[1 + rhs.size( ) + strlen(str)]( );
    strcpy(tmpStr, str);
    strcat(tmpStr, rhs.c_str( ));

    String result(tmpStr);
    delete[] tmpStr;

    // cout << "finish operator+(const char *str, const String &rhs)" << endl;
    return result;
}


int main(void) {
    // Test case 1: Default constructor
    String emptyStr;
    cout << "Empty string test: " << emptyStr.c_str( )
         << ", size: " << emptyStr.size( ) << endl;

    // Test case 2: Constructor with C-style string
    String str1("Hello, World!");
    cout << "Constructor with C-string: '" << str1.c_str( )
         << "', size: " << str1.size( ) << endl;

    // Test case 3: Copy constructor
    String str2(str1);
    cout << "Copy constructor: '" << str2.c_str( )
         << "', size: " << str2.size( ) << endl;

    // Test case 4: Assignment operator from another String
    String str3;
    str3 = str1;
    cout << "Assigned from another String: '" << str3.c_str( )
         << "', size: " << str3.size( ) << endl;

    // Test case 5: Assignment operator from C-style string
    str3 = "Modified string";
    cout << "Assigned from C-string: '" << str3.c_str( )
         << "', size: " << str3.size( ) << endl;

    // Test case 6: Concatenation using '+=' operator with String
    str1 += str2;
    cout << "Concatenation with String: '" << str1.c_str( )
         << "', size: " << str1.size( ) << endl;

    // Test case 7: Concatenation using '+=' operator with C-style string
    str2 += " concatenate";
    cout << "Concatenation with C-string: '" << str2.c_str( )
         << "', size: " << str2.size( ) << endl;

    // Test case 8: Equality and inequality operators
    str1 = "abc";
    str2 = "abc";
    cout << "Comparing 'Hello, World!' to itself: "
         << (str1 == str2 ? "Equal" : "Not Equal") << endl;
    cout << "Comparing 'Hello, World!' to 'Modified string': "
         << (str1 != str2 ? "Not Equal" : "Equal") << endl;

    // Test case 9: Less than, greater than, less than or equal, greater than or
    // equal operators
    cout << "'Hello' < 'World': "
         << (String("Hello") < String("World") ? "True" : "False") << endl;
    cout << "'Hello' > 'World': "
         << (String("Hello") > String("World") ? "True" : "False") << endl;
    cout << "'Hello' > 'Hello': "
         << (String("Hello") > String("Hello") ? "True" : "False") << endl;
    cout << "'Hello' <= 'World': "
         << (String("Hello") <= String("World") ? "True" : "False") << endl;
    cout << "'Hello' >= 'World': "
         << (String("Hello") >= String("World") ? "True" : "False") << endl;
    cout << "'Hello' >= 'Hello': "
         << (String("Hello") >= String("Hello") ? "True" : "False") << endl;
    cout << "'Hello' > 'Hello': "
         << (String("Hello") > String("Hello") ? "True" : "False") << endl;
    cout << "'Hello' <= 'Hello': "
         << (String("Hello") <= String("Hello") ? "True" : "False") << endl;
    cout << "'Hello' < 'Hello': "
         << (String("Hello") < String("Hello") ? "True" : "False") << endl;
    cout << "'Hello' == 'Hello1': "
         << (String("Hello") == String("Hello1") ? "True" : "False") << endl;
    cout << "'Hello' <= 'Hello1': "
         << (String("Hello") <= String("Hello1") ? "True" : "False") << endl;

    // Test case 10: Output stream operator
    cout << "Output stream test: " << str1 << endl;

    // Test case 11: Input stream operator (Assuming there's a line of text
    // ready in stdin)
    String inputStr;
    std::cin >> inputStr;
    cout << "Input stream test: '" << inputStr << "'" << endl;

    // Test case 12: '+' operator for concatenation
    String concatenated =
        "Zero Part " + String("First part ") + String("-- ") + "Second part";
    cout << "Concatenation with + operator: '" << concatenated.c_str( )
         << "', size: " << concatenated.size( ) << endl;

    String fileStr;
    std::ifstream ifs("2.cc");
    while (ifs >> fileStr) {
        cout << fileStr << endl;
    }
    ifs.close( );


    String numstr("104514");
    cout << "before modify: " << numstr << endl;
    char aa = numstr[0];
    ++aa;
    char &bb = numstr[1];
    ++bb;
    char &zz = numstr[-1];
    cout << zz;
    zz = 'z';
    cout << zz;
    char &zzz = numstr[111];
    cout << zzz;
    zzz = '@';
    cout << zzz << endl;
    cout << "after modify: " << numstr << endl;

    const String constStr("1919810");
    // char &cc = constStr[0]; // ERROR

    const char &cc = constStr[0]; // ERROR
    //++cc; //ERROR

    return 0;
}
