/*
 * @lc app=leetcode.cn id=57 lang=cpp
 * @lcpr version=30122
 *
 * [57] 插入区间
 */


// @lcpr-template-start
#include <algorithm>
#include <cstddef>
#include <leetcode.h>
#include <vector>
using namespace std;
// @lcpr-template-end
// @lc code=start
/*
 * @lc app=leetcode.cn id=57 lang=cpp
 * @lcpr version=30122
 *
 * [57] 插入区间
 */


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
        if (intervals.empty( )) {
            return { newInterval };
        }

        if (intervals.back( )[1] < newInterval[0]) {
            intervals.emplace_back(newInterval);
        }


        int index = 0;
        while (intervals[index][1] < newInterval[0]) {
            ++index;
        }


        if (newInterval[1] < intervals[index][0]) {
            intervals.emplace(intervals.begin( ) + index, newInterval);
        } else {
            intervals[index][0] = min(intervals[index][0], newInterval[0]);
            intervals[index][1] = max(intervals[index][1], newInterval[1]);
        }


        int replaceIndex = ++index;

        while (index != intervals.size( )) {
            if (newInterval[1] >= intervals[index][1]) {
                ++index;
                continue;
            }

            if (newInterval[1] >= intervals[index][0]) {
                intervals[replaceIndex - 1][1] = max(newInterval[1], intervals[index++][1]);
            }
            break;
        }

        intervals.erase(intervals.begin( ) + replaceIndex, intervals.begin( ) + index);

        return intervals;
    }
};

// @lc code=end


/*
// @lcpr case=start
// [[1,3],[6,9]]\n[2,5]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2],[3,5],[6,7],[8,10],[12,16]]\n[4,8]\n
// @lcpr case=end

 */
