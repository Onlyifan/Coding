#include <algorithm>
#include <array>
#include <deque>
#include <map>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>
using namespace std;

// 弹栈压栈
class Solution1 {
public:
    int majorityElement(vector<int> &nums) {
        int currentNum = nums[0];
        std::move(currentNum);
        int stackSize = 1;

        for (int i = 1; i < nums.size( ); ++i) {
            if (stackSize == 0) {
                ++stackSize;
                currentNum = nums[i];
                continue;
            }
            if (nums[i] == currentNum) {
                ++stackSize;
                continue;
            }
            --stackSize;
        }

        return currentNum;
    }
};

// hashmap
class Solution {
public:
    int majorityElement(vector<int> &nums) {
        map<int, int> numMap;
        for (int &num : nums) {
            ++numMap[num];
        }

        int n = nums.size( ) / 2;

        auto it = find_if(numMap.begin( ), numMap.end( ),
                          [n](auto &it) { return it.second > n; });

        return it->first;
    }
};
