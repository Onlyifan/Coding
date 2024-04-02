#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


template <typename T> void destroy(T *p) {
    cout << "before destroy" << endl;
    p->~T( );
    cout << "after destroy" << endl;
}

int main(void) {
    int *p = new int(3);
    destroy(p);
    delete p;

    return 0;
}
