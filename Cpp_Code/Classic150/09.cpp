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
    bool canJump(vector<int> &nums) {
        int MaxLength = nums.front( ) + 1;
        int index = 0;
        while (index < nums.size( ) && index < MaxLength) {
            MaxLength = max(index + nums[index] + 1, MaxLength);
            if (MaxLength >= nums.size( )) {
                return true;
            }
            ++index;
        }

        return false;
    }
};
