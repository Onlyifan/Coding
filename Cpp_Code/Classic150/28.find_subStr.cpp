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
    int strStr(string haystack, string needle) {
        vector<short> next(needle.size( ));


        int prefixLen = 0;
        for (int i = 1; i != next.size( );) {
            if (needle[i] == needle[prefixLen]) {
                next[i++] = ++prefixLen;
            } else {
                if (0 == prefixLen) {
                    next[i++] = 0;
                } else {
                    prefixLen = next[prefixLen - 1];
                }
            }
        }

        prefixLen = 0;
        for (int i = 0; i != haystack.size( );) {
            if (haystack[i] == needle[prefixLen]) {
                ++i;
                ++prefixLen;
            } else {
                if (0 == prefixLen) {
                    ++i;
                } else {
                    prefixLen = next[prefixLen - 1];
                }
            }

            if (needle.size( ) == prefixLen) {
                return i - prefixLen;
            }
        }

        return -1;
    }
};
