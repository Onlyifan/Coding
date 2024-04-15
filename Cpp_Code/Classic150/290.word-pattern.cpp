/*
 * @lc app=leetcode.cn id=290 lang=cpp
 * @lcpr version=30122
 *
 * [290] 单词规律
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        string                      alphaMap[26];
        unordered_map<string, char> wordMap;
        
        
        
        stringstream ss(s);
        string       word;
        

        for (int i = 0; i != pattern.size( ); ++i) {
            ss >> word;
            if (word.empty( )) {
                return false;
            }

            if (alphaMap[pattern[i] - 'a'].empty( )) {
                auto it = wordMap.find(word);
                if (it == wordMap.end( )) {
                    wordMap[word] = pattern[i];
                } else {
                    if (it->second != pattern[i]) {
                        return false;
                    }
                }
                alphaMap[pattern[i] - 'a'] = word;

            } else {
                if (word != alphaMap[pattern[i] - 'a']) {
                    return false;
                }
            }
        }

        word.clear();
        ss >> word;
        if (!word.empty()) {
            return false;
        }

        return true;
    }
};
// @lc code=end


/*
// @lcpr case=start
// "abba"\n"dog cat cat dog"\n
// @lcpr case=end

// @lcpr case=start
// "abba"\n"dog cat cat fish"\n
// @lcpr case=end

// @lcpr case=start
// "aaaa"\n"dog cat cat dog"\n
// @lcpr case=end

 */
