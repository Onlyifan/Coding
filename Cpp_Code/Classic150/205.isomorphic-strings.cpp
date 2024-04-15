/*
 * @lc app=leetcode.cn id=205 lang=cpp
 * @lcpr version=30122
 *
 * [205] 同构字符串
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start

// 利用符号位存储

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        uint8_t alphaMap[127] = {0};

        

        for (int i = 0; i != s.size( ); ++i) {
            if ((alphaMap[s[i]] & 0b01111111) == 0) {
                if (alphaMap[t[i]] & 0b10000000) {
                    return false;
                }
                alphaMap[t[i]] ^= 0b10000000;
                alphaMap[s[i]] ^= t[i];
            } else {
                if ((alphaMap[s[i]] & 0b01111111 ^ t[i]) != 0) {
                    return false;
                }
            }
        }
        return true;
    }
};


int main (){
    string s = "paper";
    string t = "title";

    Solution sol;
    sol.isIsomorphic(s, t);

    return 0;
}

class Solution1 {
public:
    bool isIsomorphic(string s, string t) {
        char alphaMap[127] = {0};
        
        bool usedMap[127] = {false};

        for (int i = 0; i != s.size( ); ++i) {
            if (alphaMap[s[i]] == 0) {
                if (usedMap[t[i]]) {
                    return false;
                }
                usedMap[t[i]] = true;
                alphaMap[s[i]] = t[i];
            } else {
                if (alphaMap[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};
// @lc code=end


/*
// @lcpr case=start
// "egg"\n"add"\n
// @lcpr case=end

// @lcpr case=start
// "foo"\n"bar"\n
// @lcpr case=end

// @lcpr case=start
// "paper"\n"title"\n
// @lcpr case=end

 */
