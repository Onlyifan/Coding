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


class Solution1 {
  public:
    string reverseWords(string s) {
        string result;
        string word;
        istringstream iss(s);
        while (iss >> word) {
            result.insert(0, " ");
            result.insert(0, word);
        }
        result.pop_back( );
        return result;
    }
};


class Solution {
  public:
    string reverseWords(string s) {
        string result;
        int index = s.size( );
        int length = 0;

        while (index != 0) {
            while (s[index - 1] == ' ') {
                --index;
                if (index == 0) {
                    result.pop_back( );
                    return result;
                }
            }
            while (index != 0 && s[index - 1] != ' ') {
                --index;
                ++length;
            }
            result += s.substr(index, length) + " ";
            length = 0;
        }

        result.pop_back( );
        return result;
    }
};
