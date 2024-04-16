/*
 * @lc app=leetcode.cn id=219 lang=cpp
 * @lcpr version=30122
 *
 * [219] 存在重复元素 II
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end


// 滑动窗口
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> window;

        for (int i = 0; i != nums.size(); ++i) {
            auto it = window.find(nums[i]);

            if (it == window.end()) {
                window.insert(nums[i]);
                if (window.size() > k) {
                    window.erase(nums[i - k]);
                }

            } else {
                return true;
            }
        }

        return false;
    }
};


// 哈希map
class Solution1 {
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int> map;

        for (int i = 0; i != nums.size( ); ++i) {
            auto it = map.find(nums[i]);
            if (it == map.end( )) {
                map.emplace(nums[i], i);
            } else {
                if (i - it->second <= k) {
                    return true;
                } else {
                    it->second = i;
                }
            }
        }

        return false;
    }
};

// @lc code=end


/*
// @lcpr case=start
// [1,2,3,1]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1,0,1,1]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,1,2,3]\n2\n
// @lcpr case=end

 */
