/*
 * @lc app=leetcode.cn id=202 lang=cpp
 * @lcpr version=30122
 *
 * [202] 快乐数
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start


// 用哈希表记录已经出现过的数
class Solution1 {
public:
    bool isHappy(int n) {
        unordered_set<int>  occured;
        occured.emplace(n);

        while (n!=1) {
            n = calculate(n);
            if (occured.count(n)) {
                return false;
            }
            occured.emplace(n);
        }

        return true;

    }

    int calculate(int n) {
        int ret = 0;
        while (n != 0) {
            int currentBit = n % 10;
            ret += currentBit * currentBit;
            n /= 10;
        }

        return ret;
    }

};


// 用数组记录已经出现过的数
class Solution {
public:
    bool isHappy(int n) {
        bool occured[731];

        while (n != 1) {
            n = calculate(n);
            if (occured[n] == true) {
                return false;
            }
            occured[n] = true;
        }

        return true;
    }

    int calculate(int n) {
        int ret = 0;
        while (n != 0) {
            int currentBit = n % 10;
            ret += currentBit * currentBit;
            n /= 10;
        }

        return ret;
    }
};

int main(){
    Solution1 s;
    s.isHappy(1999);
}
// @lc code=end



/*
// @lcpr case=start
// 19\n
// @lcpr case=end

// @lcpr case=start
// 2\n
// @lcpr case=end

 */

