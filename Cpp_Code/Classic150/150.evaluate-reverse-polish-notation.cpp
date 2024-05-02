/*
 * @lc app=leetcode.cn id=150 lang=cpp
 * @lcpr version=30122
 *
 * [150] 逆波兰表达式求值
 */


// @lcpr-template-start
#include <cctype>
#include <leetcode.h>
#include <stack>
#include <string>
using namespace std;
// @lcpr-template-end
// @lc code=start


// -= *= 更装
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        vector<int> result;
        int stackTop = -1;

        for (auto &elem : tokens) {
            if (elem.size( ) != 1 || isdigit(elem[0])) {
                ++stackTop;
                if (stackTop != result.size( )) {
                    result[stackTop] = stoi(elem);
                } else {
                    result.emplace_back(stoi(elem));
                }
                continue;
            }

            --stackTop;
            calculate(result[stackTop], result[stackTop + 1], elem[0]);
        }

        return result.front( );
    }


private:
    static void calculate(int &lhs, const int &rhs, char op) {
        switch (op) {
        case '+':
            lhs += rhs;
            return;
        case '-':
            lhs -= rhs;
            return;
        case '*':
            lhs *= rhs;
            return;
        default:
            lhs /= rhs;
            return;
        }
    }
};
// @lc code=end


/*
// @lcpr case=start
// ["2","1","+","3","*"]\n
// @lcpr case=end

// @lcpr case=start
// ["4","13","5","/","+"]\n
// @lcpr case=end

// @lcpr case=start
// ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]\n
// @lcpr case=end

 */
