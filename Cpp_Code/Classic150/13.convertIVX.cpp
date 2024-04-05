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
    int romanToInt(string s) {
        short result = 0;

        for (int i = 0; i != s.size( ); ++i) {
            switch (s[i]) {
            case 'I':
                
                if (i == s.size( ) - 1) {
                    return result + 1;
                }
                if (s[i + 1] == 'V') {
                    result += 4;
                    ++i;
                    break;
                }
                if (s[i + 1] == 'X') {
                    result += 9;
                    ++i;
                    break;
                }
                result += 1;
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                
                if (i == s.size( ) - 1) {
                    return result + 10;
                }
                if (s[i + 1] == 'L') {
                    result += 40;
                    ++i;
                    break;
                }
                if (s[i + 1] == 'C') {
                    result += 90;
                    ++i;
                    break;
                }
                result += 10;
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                if (i == s.size( ) - 1) {
                    return result + 100;
                }
                if (s[i + 1] == 'D') {
                    result += 400;
                    ++i;
                    break;
                }
                if (s[i + 1] == 'M') {
                    result += 900;
                    ++i;
                    break;
                }

                result += 100;
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
            }
        }
        return result;
    }
};

