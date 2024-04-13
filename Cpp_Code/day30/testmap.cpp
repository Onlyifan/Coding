#include <leetcode.h>
#include <memory>
#include <utility>
using namespace std;


class Test {
  public:
    Test(int x)
        : _x(x) {}

  public:
    int _x;
};

void test( ) {

    // map.insert(make_pair(3, shared_ptr<Test>(new Test(3))));
    // map.emplace(make_pair(3, shared_ptr<Test>(new Test(3))));
    // map.insert(make_pair(3, new Test(3)));

}

int main( ) {
    test( );


    return 0;
}
