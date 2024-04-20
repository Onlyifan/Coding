/*
 * @lc app=leetcode.cn id=128 lang=cpp
 * @lcpr version=30122
 *
 * [128] 最长连续序列
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, bool> unionNums;

        for (auto &num : nums) {
            auto prefixIt = unionNums.find(num - 1);
            auto suffixIt = unionNums.find(num + 1);

            bool r1 = prefixIt != unionNums.end( ) && prefixIt->second == false;
            bool r2 = prefixIt != unionNums.end( ) && prefixIt->second == true;

            if (r1 && r2) {
                
            }


            }

        }

    }
};
// @lc code=end



/*
// @lcpr case=start
// [100,4,200,1,3,2]\n
// @lcpr case=end

// @lcpr case=start
// [0,3,7,2,5,8,4,6,0,1]\n
// @lcpr case=end

 */

