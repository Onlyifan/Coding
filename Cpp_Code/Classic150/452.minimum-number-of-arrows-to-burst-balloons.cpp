/*
 * @lc app=leetcode.cn id=452 lang=cpp
 * @lcpr version=30122
 *
 * [452] 用最少数量的箭引爆气球
 */


// @lcpr-template-start
#include <algorithm>
#include <leetcode.h>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int findMinArrowShots(vector<vector<int>> &points) {
        sort(points.begin( ), points.end( ), [](vector<int> &a, vector<int> &b) { return a[0] > b[0]; });

        int result = 1;

        // 无状态的思想
        int L = points[0][0];

        for (int i = 1; i != points.size( ); ++i) {
            if (points[i][1] < L) {
                L = points[i][0];
                ++result;
            }
        }


        return result;
    }
};
// @lc code=end


/*
// @lcpr case=start
// [[10,16],[2,8],[1,6],[7,12]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,4],[5,6],[7,8]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[2,3],[3,4],[4,5]]\n
// @lcpr case=end

 */
