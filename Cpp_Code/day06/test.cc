#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main(void) {
    vector<int> myVector(10, 5);

    cout << myVector.size( ) << endl;
    cout << myVector.capacity( ) << endl;

    for (auto &num : myVector) {
        cout << num << " ";
    }
    cout << *myVector.end( );
    cout << *(myVector.end( ) + 1);
    cout << endl;

    *myVector.end( ) = 1;
    *(myVector.end( ) - 1) = 1;
    *(myVector.end( ) + 1) = 1;

    for (auto &num : myVector) {
        cout << num << " ";
    }
    cout << *myVector.end( );
    cout << *(myVector.end( ) + 1);
    cout << endl;

    return 0;
}
