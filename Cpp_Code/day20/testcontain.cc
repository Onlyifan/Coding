#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::multiset;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_multiset;
using std::unordered_set;


int main(void) {
    set<int> set1;
    // set1.insert(1);
    // multiset<int> set2;
    // set2.insert();
    // set1.insert();


    map<int, int> map1;
    // int a = map1.at(1);
    int a = map1[1];

    auto it = map1.begin( );
    it->second++;

    cout << a << endl;

    multimap<int, int> map2;
    it = map2.begin( );
    it->second++;

    unordered_set<int> uset1;
    uset1.

    return 0;
}
