#include <iostream>
#include <list>
#include <string>
using std::cout;
using std::endl;
using std::list;
using std::string;


int main(void) {
    list<int> lst;
    list<int>::iterator iter1 = lst.begin( ), iter2 = lst.end( );
    while (iter1 < iter2) {
        //....
    }

    return 0;
}
