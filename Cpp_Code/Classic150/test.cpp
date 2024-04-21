#include <iostream>
#include <set>
using namespace std; 

int main( ) {

    set<bool> mainset;

    mainset.insert(true);
    mainset.insert(false);
    mainset.insert(true);


    for (auto &i : mainset) {
        cout << i << endl;
    }

    

    return 0;
}