/*
 * @lc app=leetcode.cn id=71 lang=cpp
 * @lcpr version=30122
 *
 * [71] 简化路径
 */


// @lcpr-template-start
#include <leetcode.h>
#include <sstream>
#include <stack>
#include <string>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    string simplifyPath(string path) {
        for (auto &ch : path) {
            if (ch == '/') {
                ch = ' ';
            }
        }

        istringstream iss(path);

        string word;

        vector<string> pathStack;

        while (iss >> word) {
            if (word == ".") {
                continue;
            } else if (word == "..") {
                if (!pathStack.empty( )) {
                    pathStack.pop_back( );
                }

            } else {
                pathStack.push_back(word);
            }
        }


        string result;

        for (auto &word : pathStack) {
            result += "/" + word;
        }
        return result;
    }
};
// @lc code=end


/*
// @lcpr case=start
// "/home/"\n
// @lcpr case=end

// @lcpr case=start
// "/../"\n
// @lcpr case=end

// @lcpr case=start
// "/home//foo/"\n
// @lcpr case=end

// @lcpr case=start
// "/a/./b/../../c/"\n
// @lcpr case=end

 */
