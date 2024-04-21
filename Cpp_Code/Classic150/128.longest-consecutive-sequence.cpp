/*
 * @lc app=leetcode.cn id=128 lang=cpp
 * @lcpr version=30122
 *
 * [128] 最长连续序列
 */


// @lcpr-template-start
#include <algorithm>
#include <leetcode.h>
#include <unordered_set>
using namespace std;

// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        unordered_set<int> hashNums;


        for (auto &num : nums) {
            hashNums.emplace(num);
        }

        int length = 0;

        //第二次要遍历hash_set, 因为天然去重
        for (auto &num : hashNums) {
            if (hashNums.count(num - 1)) {
                continue;
            }

            if (!hashNums.count(num + length)) {
                continue;
            }

            int tmp = 1;
            while (hashNums.count(num + tmp)) {
                // hashNums.erase(num + tmp);
                ++tmp;
            }
            length = max(length, tmp);
        }

        return length;
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
