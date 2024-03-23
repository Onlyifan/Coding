#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


// int print( ) {
//     return -1;
// }
template <class T, class... Args>

void print(T x, Args... args) {
    cout << x << " ";

    print(args...);
}


int main(void) {

    print(1, 2, 3, 4, 5);


    return 0;
}
