/*
 * @lc app=leetcode.cn id=49 lang=cpp
 * @lcpr version=30122
 *
 * [49] 字母异位词分组
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution1 {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<string, vector<int>> groupIndex;

        for (int i = 0; i != strs.size( ); ++i) {
            string str(strs[i]);
            sort(str.begin( ), str.end( ));
            groupIndex[str].push_back(i);
        }
        vector<vector<string>> result;

        for (auto it = groupIndex.begin( ); it != groupIndex.end( ); ++it) {
            vector<string> tmp;
            for (auto index : it->second) {
                tmp.push_back(strs[index]);
            }
            result.push_back(std::move(tmp));
        }

        return result;
    }
};


// 一个比较暴力的哈希函数
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        unordered_map<uint64_t, vector<string>> groupIndex;

        for (const auto & i : strs) {
            uint64_t hashNum = i.size();
            for (auto ch : i) {
                hashNum += ch;
                hashNum += (uint64_t)1 << (ch - 'a' + 16);
            }

            groupIndex[hashNum].push_back(i);
        }
        vector<vector<string>> result;
        result.reserve(groupIndex.size());
        
        for (auto it = groupIndex.begin( ); it != groupIndex.end( ); ++it) {
            result.push_back(std::move(it->second));
        }

        return result;
    }
};

// @lc code=end


/*
// @lcpr case=start
// ["eat", "tea", "tan", "ate", "nat", "bat"]\n
// @lcpr case=end

// @lcpr case=start
// [""]\n
// @lcpr case=end

// @lcpr case=start
// ["a"]\n
// @lcpr case=end

 */
