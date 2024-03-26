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
    vector<int> vec{1, 2, 3, 4, 5};
    display(vec);
    auto it = vec.begin( );
    ++it;
    vec.insert(vec.end( ), {1, 2, 3, 4, 5});
    cout << *it << endl;
    display(vec);
    vec.insert(it + 3, {1, 2, 3});
    display(vec);


    return 0;
}
