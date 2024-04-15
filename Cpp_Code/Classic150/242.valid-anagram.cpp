/*
 * @lc app=leetcode.cn id=242 lang=cpp
 * @lcpr version=30122
 *
 * [242] 有效的字母异位词
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        short alphaCount[127];
        
        for (auto &ch : t) {
            ++alphaCount[ch];
        }

        for (auto &ch : s) {
            if (alphaCount[ch] == 0) {
                return false;
            }
            --alphaCount[ch];
        }

        return true;
    }
};
// @lc code=end



/*
// @lcpr case=start
// "anagram"\n"nagaram"\n
// @lcpr case=end

// @lcpr case=start
// "rat"\n"car"\n
// @lcpr case=end

 */

