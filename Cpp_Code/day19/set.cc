#include <functional>
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;


struct Compare {
    bool com(const int &, const int &);
};

int main(void) {
    set<int, std::greater<int>> s1;
    std::greater<int> g;
    // std::set<int, Compare> peopleByAge([](const int &a, const int &b) { return a < b; });
    // std::set<int> aset([](const int &a, const int &b) { return a < b; });

    return 0;
}
