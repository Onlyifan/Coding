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
    bool isValid(string s) {
        stack<char, vector<char>> strStack;
        for (char ch : s) {
            switch (ch) {
            case '{':
                strStack.emplace('}');
                break;
            case '[':
                strStack.emplace(']');
                break;
            case '(':
                strStack.emplace(')');
                break;
            default:
                if (strStack.empty( )) {
                    return false;
                }
                if (strStack.top( ) != ch) {
                    return false;
                }

                strStack.pop( );
            }
        }

        if (strStack.empty( )) {
            return true;
        }
        return false;
    }
};
