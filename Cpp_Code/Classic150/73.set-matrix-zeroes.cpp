/*
 * @lc app=leetcode.cn id=73 lang=cpp
 * @lcpr version=30122
 *
 * [73] 矩阵置零
 */


// @lcpr-template-start
#include <leetcode.h>
#include <memory>
using namespace std;
// @lcpr-template-end
// @lc code=start


class Solution {
  public:
    void setZeroes(vector<vector<int>> &matrix) {

        
        bool upper = false;
        bool left = false;
        

        
        if (matrix[0][0] == 0) {
            upper = true;
            left = true;
        } else {

            for (int i = 1; i != matrix.size( ); ++i) {
                if (matrix[i][0] == 0) {
                    left = true;
                    break;
                }
            }

            for (int i = 1; i != matrix[0].size( ); ++i) {
                if (matrix[0][i] == 0) {
                    upper = true;
                    break;
                }
            }
        }

        for (int i = 1; i != matrix.size( ); ++i) {
            for (int j = 1; j != matrix[0].size( ); ++j) {
                if (matrix[i][j] == 0) {

                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int i = 1; i != matrix.size( ); ++i) {
            for (int j = 1; j < matrix[0].size( ); ++j) {

                if (!matrix[i][0] || !matrix[0][j]) {
                    matrix[i][j] = 0;
                }

            }
        }

        if (upper == true) {
            for (int j = 0; j != matrix[0].size( ); ++j) {
                matrix[0][j] = 0;
            }
        }
        if (left == true) {
            for (int i = 0; i != matrix.size( ); ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};
// @lc code=end


/*
// @lcpr case=start
// [[1,1,1],[1,0,1],[1,1,1]]\n
// @lcpr case=end

// @lcpr case=start
// [[0,1,2,0],[3,4,5,2],[1,3,1,5]]\n
// @lcpr case=end

     */