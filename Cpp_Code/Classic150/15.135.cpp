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


class Solution {
  public:
    int candy(vector<int> &ratings) {
        int size = ratings.size( );

        if (1 == ratings.size( )) {
            return 1;
        }

        if (2 == ratings.size( )) {
            return 2 + (ratings.front( ) != ratings.back( ));
        }

        for (int i = 0; i != size - 1; ++i) {
            ratings[i] = ratings[i + 1] - ratings[i];
        }

        int sum = 0;

        int i = 0;

        return ratings.size( ) + sum;
    }
};
