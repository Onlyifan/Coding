/*
 * @lc app=leetcode.cn id=56 lang=cpp
 * @lcpr version=30122
 *
 * [56] 合并区间
 */


// @lcpr-template-start
// @lcpr-template-end
// @lc code=start
#include <algorithm>
#include <climits>
#include <leetcode.h>
#include <map>
#include <utility>
#include <vector>
using namespace std;


// Map先储存
class Solution1 {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        multiset<pair<int, bool>> points;

        for (auto &elem : intervals) {
            points.emplace(elem[0], false);
            points.emplace(elem[1], true);
        }

        vector<vector<int>> result;

        auto it = points.begin( );

        while (it != points.end( )) {
            int count = 1;
            const int &left = it->first;
            ++it;

            for (;;) {
                if (it->second == false) {
                    ++count;
                    ++it;
                    continue;
                }

                --count;

                if (count == 0) {
                }

                ++it;
            }

            result.push_back({ left, it->first });
        }


        return result;
    }
};


// O(1)额外空间
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        vector<vector<int>> result;
        if (intervals.empty( )) {
            return result;
        }
        sort(intervals.begin( ), intervals.end( ));

        result.emplace_back(intervals[0]);

        for (int i = 1; i != intervals.size( ); ++i) {
            if (result.back( )[1] < intervals[i][0]) {
                result.emplace_back(intervals[i]);
                continue;
            }

            result.back( )[1] = max(result.back( )[1], intervals[i][1]);
        }

        return result;
    }
};


int main( ) {
    Solution s;
    vector<vector<int>> arr{ { 1, 3 }, { 2, 6 }, { 8, 10 } };
    s.merge(arr);
}
// @lc code=end


/*
// @lcpr case=start
// [[1,3],[2,6],[8,10],[15,18]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,4],[4,5]]\n
// @lcpr case=end

 */
