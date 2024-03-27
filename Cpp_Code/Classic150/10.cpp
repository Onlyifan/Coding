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

// 笨办法
class Solution1 {
  public:
    int jump(vector<int> &nums) {
        vector<int> counts(nums.size( ), std::numeric_limits<int>::max( ));
        counts[0] = 0;
        for (int i = 0; i != nums.size( ) - 1; ++i) {
            int currentCount = counts[i];
            transform(counts.begin( ) + i + 1,
                      min(counts.end( ), counts.begin( ) + i + 1 + nums[i]),
                      counts.begin( ) + i + 1,
                      [currentCount](int num) { return min(num, currentCount + 1); });
            if (counts.back( ) != std::numeric_limits<int>::max( )) {
                return counts.back( );
            }
        }
        return counts.back( );
    }
};


class Solution {
  public:
    int jump(vector<int> &nums) {
        int index = 0;
        int count = 0;
        int maxIndex = 0;
        int size = nums.size( ) - 2;
        for (;;) {
            if (maxIndex + 1 >= nums.size( )) {
                return count;
            }

            int tmpIndex = maxIndex;
            while (index <= maxIndex) {
                tmpIndex = max(tmpIndex, index + nums[index]);
                ++index;
            }

            ++count;
            maxIndex = tmpIndex;
        }
    }
};
