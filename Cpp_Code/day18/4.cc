#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::map;
using std::set;
using std::vector;


class Int {
    friend bool operator<(const Int v1, const Int v2);

  public:
    Int(int i)
        : _i(i) {}

  private:
    int _i;
};

bool operator<(const Int v1, const Int v2) {
    return v1._i < v2._i;
}

int main(void) {
    // vector<int> v1{1, 2, 3, 4};
    // vector<int> v2{2, 2, 3};
    // deque<int> v1{1,2,3,4};
    // deque<int> v2{2,2,3};
    // list<int> v1{1,2,3,4};
    // list<int> v2{2,2,3};
    // map<int, int> v1{{1,1}, {2, 999}, {3,999}};
    // map<int, int> v2{{0,999}, {2, 999}, {3,999}};
    // map<int, int> v2{{2,2}};
    // set<int> v1{1, 2, 3};
    // set<int> v2{0, 1, 2, 4};
    // vector<Int> v1{1, 2, 3};
    // vector<Int> v2{1, 2, 3};


    if (v1 < v2) {
        cout << "v1 < v2" << endl;
    } else {
        cout << "v1 not < v2" << endl;
    }

    return 0;
}
