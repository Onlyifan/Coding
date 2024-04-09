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
    int minSubArrayLen(int target, vector<int> &nums) {
        int left = -1;
        int length = std::numeric_limits<int>::max( );
        // int length = INT_MAX;
        int sum = 0;

        for (int i = 0; i != nums.size( ); ++i) {
            sum += nums[i];
            while (sum >= target) {
                length = min(i - left, length);
                if (length == 1) {
                    return 1;
                }
                sum -= nums[++left];
            }
        }
        if (left == -1) {
            return 0;
        }
        return length;
    }
};
