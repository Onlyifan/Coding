#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;


template <typename Contain> void display(const Contain &con) {
    for (auto it = con.begin( ); it != con.end( ); ++it) {
        cout << *it << "-";
    }
    cout << endl;

    for (int i = 0; i != con.size( ); ++i) {

        cout << con[i] << "-";
    }
    cout << endl;

    for (auto &element : con) {
        cout << element << "-";
    }
    cout << endl;
}


int main(void) {
    vector<string> v1;
    display(v1);

    vector<int> v2 = {1, 2, 3};
    display(v2);
    vector<string> v3{"abc", "123"};
    display(v3);
    vector<int> v4(5);
    display(v4);
    vector<string> v5(3, "abc");
    display(v5);


    return 0;
}
