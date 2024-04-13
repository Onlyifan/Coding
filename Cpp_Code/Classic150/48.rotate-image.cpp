// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=48 lang=cpp
 * @lcpr version=30122
 *
 * [48] 旋转图像
 */


// @lcpr-template-start
#include <leetcode.h>
#include <map>
#include <memory>
#include <vector>

using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    vector<vector<int>> tmp(matrix);
    for (int i = 0; i < matrix.size() / 2; ++i) {
      for (int j = 0; j < (matrix.size() + 1) / 2; ++j) {
        swapFour(matrix, i, j);
      }
    }
  }

private:
  void swapFour(vector<vector<int>> &matrix, int x, int y) {
    // 左下, 逆时针
    int maxIndex = matrix.size() - 1;
    int tmp = matrix[x][y];

    matrix[x][y] = matrix[maxIndex - y][x];
    matrix[maxIndex - y][x] = matrix[maxIndex - x][maxIndex - y];
    matrix[maxIndex - x][maxIndex - y] = matrix[y][maxIndex - x];
    matrix[y][maxIndex - x] = tmp;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]\n
// @lcpr case=end

 */
