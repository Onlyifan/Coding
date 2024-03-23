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
    int removeDuplicates(vector<int> &nums) {
        if (nums.size( ) == 0) {
            return 0;
        }

        bool alreadyAppear = false;

        int slow = 0;
        int fast = 1;


        while (fast < nums.size( )) {
            if (nums[slow] != nums[fast]) {
                nums[++slow] = nums[fast];
                alreadyAppear = false;

            } else if (alreadyAppear == false) {

                nums[++slow] = nums[fast];
                alreadyAppear = true;
            }
            ++fast;
        }
        return slow + 1;
    }
};


class Solution {
  public:
    int removeDuplicates(vector<int> &nums) {
        size_t size = nums.size( );
        if (size <= 2) {
            return size;
        }

        int slow = 2;
        int fast = 2;

        while (fast < size) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow++] = nums[fast];
            }
            ++fast;
        }

        return slow;
    }
};
