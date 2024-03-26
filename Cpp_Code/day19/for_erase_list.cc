#include <iostream>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;

int main(void) {
    list<int> ls{1, 2, 3, 4, 5};
    for (auto it = ls.begin( ); it != ls.end( ); ++it) {
        if (*it == 3) {
            ls.erase(it);
        }
    }

    vector<int> vq;
    

    return 0;
}
