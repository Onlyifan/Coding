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
    vector<int> twoSum(vector<int> &numbers, int target) {
        int right = 0;
        while (numbers[right] < target / 2) {
            numbers[right] = target - numbers[right];
            ++right;
        }

        if (0 == right) {
            return {1, 2};
        }

        if (right + 1 != numbers.size( ) && numbers[right] + numbers[right + 1] == target) {
            return {right + 1, right + 2};
        }

        int left = right - 1;
        while (numbers[left] != numbers[right]) {
            if (numbers[left] > numbers[right]) {
                ++right;
            } else {
                --left;
            }
        }

        return {left + 1, right + 1};
    }
};


// 复习数学
// 不适合查找同时出现正负数的场合
// [-10,-8,-2,1,2,5,6]
class Solution2 {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // if (numbers.front( ) == target) {
        // return {1, 2};
        // }


        auto right = upper_bound(numbers.begin( ) + 1, numbers.end( ) - 1, target);
        // if (right == numbers.end( )) {
        // --right;
        // }


        auto left = numbers.begin( );


        for (;;) {
            int result = *left + *right - target;
            if (result > 0) {
                --right;
            } else if (result < 0) {
                ++left;
            } else {
                return {static_cast<int>(left - numbers.begin( )) + 1,
                        static_cast<int>(right - numbers.begin( )) + 1};
            }
        }
    }
};

class Solution {
  public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int left = 0;
        int right = numbers.size( ) - 1;
        for (;;) {
            int result = numbers[left] + numbers[right] - target;

            if (result > 0) {
                --right;
            } else if (result < 0) {
                ++left;
            } else {
                return {left + 1, right + 1};
            }
        }
    }
};
