/*
 * @lc app=leetcode.cn id=228 lang=cpp
 * @lcpr version=30122
 *
 * [228] 汇总区间
 */


// @lcpr-template-start
#include <leetcode.h>
#include <string>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    vector<string> summaryRanges(vector<int> &nums) {
        vector<string> result;

        int index = 0;
        int left;

        while (index != nums.size( )) {
            left = nums[index];

            while (index + 1 != nums.size( ) && nums[index] + 1 == nums[index + 1]) {
                ++index;
            }

            if (left == nums[index]) {
                result.emplace_back(to_string(left));
            } else {
                result.emplace_back(to_string(left) + "->" + to_string(nums[index]));
            }
            ++index;
        }

        return result;
    }
};
// @lc code=end


/*
// @lcpr case=start
// [0,1,2,4,5,7]\n
// @lcpr case=end

// @lcpr case=start
// [0,2,3,4,6,8,9]\n
// @lcpr case=end

 */
