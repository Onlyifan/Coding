#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(void) {
    vector<int> i{1, 2, 3};
    cout << i[2] << endl;
    cout << i[3] << endl;
    i[3] = 10;
    i[4] = 10;
    i[5] = 10;
    cout << i.at(2) << endl;
    cout << i.at(3) << endl;
    // vector<int> i;
    // long *p = (long*)&i;
    // cout << p[0]<< endl;
    // cout << p[1]<< endl;
    // cout << p[2]<< endl;

    i.push_back(2);
    i.push_back(2);
    i.push_back(2);
    i.pop_back( );
    vector<int>::iterator it;
    std::deque<int> dd;
    std::list<int> ll;

    return 0;
}
