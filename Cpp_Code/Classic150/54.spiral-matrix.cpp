/*
 * @lc app=leetcode.cn id=54 lang=cpp
 * @lcpr version=30122
 *
 * [54] 螺旋矩阵
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {

        int upperBound = 0;
        int leftBound = 0;
        int rightBound = matrix.front( ).size( )  - 1;
        int bottomBound = matrix.size( ) - 1;


        vector<int> result;
        result.reserve((rightBound + 1) * (bottomBound + 1));

        for(;;) {
            for(int i = leftBound; i <= rightBound; ++i) {
                result.emplace_back(matrix[upperBound][i]);
            }

            if(++upperBound > bottomBound) {
                break;
            }

            for(int i = upperBound; i <= bottomBound; ++i) {
                result.emplace_back(matrix[i][rightBound]);
            }
            if(leftBound> --rightBound) {
                break;
            }
            
            for(int i = rightBound; i >= leftBound; --i) {
                result.emplace_back(matrix[bottomBound][i]);
            }
            if(upperBound > --bottomBound) {
                break;
            }

            for(int i = bottomBound; i >= upperBound; --i) {
                result.emplace_back(matrix[i][leftBound]);
            }
            
            if(++leftBound> rightBound) {
                break;
            }
        }
        

        return result;
    }
};
// @lc code=end


/*
// @lcpr case=start
// [[1,2,3],[4,5,6],[7,8,9]]\n
// @lcpr case=end

// @lcpr case=start
// [[1,2,3,4],[5,6,7,8],[9,10,11,12]]\n
// @lcpr case=end

 */
