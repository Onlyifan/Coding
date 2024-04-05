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
    string intToRoman(int num) {
        string result;

        array<array<const char *, 10>, 3> arr{
            array<const char *, 10>{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
            array<const char *, 10>{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
            array<const char *, 10>{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"}};

        for (int i = 0; i != num / 1000; ++i) {
            result.push_back('M');
        }
        num %= 1000;

        result += arr[0][num / 100];
        num %= 100;
        result += arr[1][num / 10];
        num %= 10;
        result += arr[2][num];

        return result;
    }
};


class Solution {
public:
    string intToRoman(int num) {
        string romeCode = "IIIVIIIXXXLXXXCCCDCCCMMM";

    }
};
