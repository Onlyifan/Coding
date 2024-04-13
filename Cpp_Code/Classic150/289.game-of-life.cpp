/*
 * @lc app=leetcode.cn id=289 lang=cpp
 * @lcpr version=30122
 *
 * [289] 生命游戏
 */

// @lcpr-template-start
#include <initializer_list>
#include <leetcode.h>
#include <string>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
  public:
    void gameOfLife(vector<vector<int>> &board) {
        _firstSize = board.size();
        _secondSize = board[0].size();

        for (int i = 0; i < _firstSize; ++i) {
            for (int j = 0; j < _secondSize; ++j) {
            }
        }
    }

private:
    bool inArea(int i, int j) {
        return i >= 0 && i >= 0 && i < _firstSize && j < _secondSize;
    }

    string _baba;
    int    _firstSize;
    int    _secondSize;
};
// @lc code=end

/*
// @lcpr case=start
// [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,1],[1,0]]\n
// @lcpr case=end

 */
