#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(void) {

    char a[200] = {0};
    cin.getline(a, 200, ' ');
    cout << a;

    return 0;
}
