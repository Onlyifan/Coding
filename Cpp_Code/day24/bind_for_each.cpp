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

using namespace std::placeholders;

class M {
  public:
    M(int m): data(m) {}
    void print( ) const { std::cout << "Data: " << data << std::endl; }
    int data;
};

int main( ) {
    std::vector<M> vecM;

    for (int i = 1; i != 11; ++i) {
        vecM.push_back(M(i));
    }

    M tmp(222);

    // function<void(M)> func = bind(&M::print, _1);
    // function<void(M *)> func = bind(&M::print, _1);
    auto func = bind(&M::print, _1);
    func(tmp);
    func(&tmp);
    std::for_each(vecM.begin( ), vecM.end( ), func);

    return 0;
}
