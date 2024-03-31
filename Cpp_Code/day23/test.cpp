#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
using namespace std;


int mut(int x, int y) {
    return 1;
}


using namespace std::placeholders;
// function<int(int, int)> f1 = bind(add, 1, _1, _2);

class T {
  public:
    T(int x)
        : data(x) {}
    int add(int x, int y, int z) {
        this->data = x + y + z;
        return x + y + z;
    }

    int data;
};


int main( ) {

    T tt(-1);
    auto f1 = bind(&T::add, &tt, 1, 2, 3);
    // auto f1 = bind(&T::add, &tt, 1, 2, 3);
    cout << f1( ) << endl;
    cout << tt.data;
}
