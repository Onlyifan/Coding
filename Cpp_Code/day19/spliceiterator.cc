#include <iostream>
#include <list>
#include <string.h>
#include <string>
using std::cout;
using std::endl;
using std::list;
using std::string;

template <typename T> void display(const T &vec) {
    for (auto &elem : vec) {
        cout << elem << " ";
    }


    cout << endl;
}


int main(void) {
    list<int> ls1{1, 2, 3, 4};
    list<int> ls2{7, 8, 9};
    auto it = ls2.begin( );
    ++it;
    cout << "*it = " << *it << endl;
    ls1.splice(ls1.begin( ), ls2);
    display(ls1);
    display(ls2);
    cout << "*it = " << *it << endl;
    ++it;
    ++it;
    ++it;
    cout << "*it+1 = " << *it << endl;


    return 0;
}
