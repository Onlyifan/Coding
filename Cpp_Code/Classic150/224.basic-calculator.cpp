/*
 * @lc app=leetcode.cn id=224 lang=cpp
 * @lcpr version=30122
 *
 * [224] 基本计算器
 */

// @lcpr-template-start
#include <cstring>
#include <stack>
#include <string>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    int calculate(string s) {
        bool isFirstOp = true;

        stack<char> opStack;
        stack<int> numStack;

        size_t i = 0;
        while (i != s.size( )) {
            const auto &ch = s[i];
            switch (ch) {
            case ' ':
                ++i;
                break;

            case '(':
                isFirstOp = true;
                ++i;
                opStack.emplace('(');
                break;

            case '-':
            case '+':
                ++i;
                if (isFirstOp) {
                    numStack.push(0);
                    isFirstOp = false;
                } else if (!opStack.empty( ) && opStack.top( ) != '(') {
                    calculateOnce(opStack, numStack);
                }
                opStack.emplace(ch);
                break;

            case ')':
                ++i;
                operateBrack(opStack, numStack);
                break;

            default:
                isFirstOp = false;
                numStack.emplace(splitNum(s, i));
            }
        }

        operateBrack(opStack, numStack);
        return numStack.top( );
    }

private:
    static int splitNum(string &str, size_t &index) {
        while (!isdigit(str[index])) {
            ++index;
        }

        size_t start = index;

        while (index != str.size( ) && ::isdigit(str[index])) {
            ++index;
        }

        return stoi(str.substr(start, index - start));
    }


    static void calculateOnce(stack<char> &opStack, stack<int> &numStack) {
        char op = opStack.top( );
        opStack.pop( );

        int rhs = numStack.top( );
        numStack.pop( );


        switch (op) {
        case '+':
            numStack.top( ) = numStack.top( ) + rhs;
            break;
        case '-':
            numStack.top( ) = numStack.top( ) - rhs;
            break;
        default:
            return;
        }
    }


    static void operateBrack(stack<char> &opStack, stack<int> &numStack) {
        for (;;) {
            if (opStack.empty( )) {
                return;
            }

            if (opStack.top( ) == '(') {
                opStack.pop( );
                return;
            }

            calculateOnce(opStack, numStack);
        }
    }
};


int main( ) {
    Solution s;
    s.calculate("1 + 1");
}