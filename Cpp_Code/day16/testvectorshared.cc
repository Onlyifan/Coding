#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;


int main(void) {
    std::shared_ptr<int> p(new int(10));
    // std::vector<std::shared_ptr<int>> v;
    cout << *p << endl;
    // v.push_back(std::move(p));
    // cout << *v[0] << endl;
    cout << *p << endl;
    cout << p.use_count( ) << endl;
    std::weak_ptr w(p);
    // cout << *w << endl;
    cout << w.lock( ).use_count( ) << endl;
    cout << p.use_count( ) << endl;

    return 0;
}
