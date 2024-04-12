#include <leetcode.h>
using namespace std;
using namespace placeholders;


class T {
  public:
    int add(int x, int y) { return x + y; }
};
int main( ) {
    T aa;
    auto me = mem_fn(&T::add);

    // function<int(int)> me = bind(&T::add, &a, 1);
    cout << me(&aa, 1, 2);
}
