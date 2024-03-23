#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;

int main(void) {
    std::unique_ptr<int> p(new int(10));

    std::vector<std::unique_ptr<int>> v;

    cout << *p << endl;
    v.push_back(std::move(p));
    cout << *v[0] << endl;
    // cout << *p << endl;


    return 0;
}
