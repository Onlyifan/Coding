#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;


void display(const vector<int> &vec) {
    for (auto &elem : vec) {
        cout << elem << " ";
    }

    cout << endl;
}

int main(void) {
    vector<int> vec{1, 3, 4, 4, 4, 6, 4, 3, 4, 7};
    for (auto it = vec.begin( ); it != vec.end( );) {
        if (*it == 4) {
            cout << "iterator = " << *vec.erase(it) << endl;
            cout << "*it = " << *it << endl;
            // it = vec.erase(it);
        } else {
            ++it;
        }
    }
    display(vec);

    return 0;
}
