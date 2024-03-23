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

// 申请了额外空间
class Solution1 {
  public:
    void rotate(vector<int> &nums, int k) {
        int oldsize = nums.size( );
        k %= oldsize;
        if (k == 0) {
            return;
        }

        nums.reserve(2 * oldsize - k);
        for (int i = 0; i < oldsize - k; ++i) {
            nums.push_back(nums[i]);
        }
        nums.erase(nums.begin( ), nums.end( ) - oldsize);
    }
};


// 真正的O(n)

class Solution2 {
  public:
    void rotate(vector<int> &nums, int k) {
        int size = nums.size( );
        k %= size;
        // gcd(0, n) == n;
        int loopCount = gcd(k, size);
        int loopLength = size / loopCount - 1;

        for (int i = 0; i < loopCount; ++i) {
            int currenetIndex = i;
            int previousIndex;
            int tmp = nums[i];

            for (;;) {
                previousIndex = (size - k + currenetIndex) % size;
                if (previousIndex == i) {
                    nums[currenetIndex] = tmp;
                    break;
                }
                nums[currenetIndex] = nums[previousIndex];
                currenetIndex = previousIndex;
            }
        }
    }
};

class Solution {
  public:
    void rotate(vector<int> &nums, int k) {
        k %= nums.size( );
        if (k == 0) {
            return;
        }

        reverse(nums.begin( ), nums.end( ));
        reverse(nums.begin( ), nums.begin( ) + k);
        reverse(nums.begin( ) + k, nums.end( ));
    }
};
