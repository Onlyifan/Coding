#include "string_highlight.hh"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(void) {

    string str("ha ha hah ha haha hah");
    string str1("ha");
    string str2("hah");
    string str3("haha");

    cout << render::highlightSubStr(str, str1, str2, str3) << endl;
    cout << render::highlightSubStr(str) << endl;


    return 0;
}
