/*
 * @lc app=leetcode.cn id=383 lang=cpp
 * @lcpr version=30122
 *
 * [383] 赎金信
 */


// @lcpr-template-start
#include <leetcode.h>
using namespace std;
// @lcpr-template-end
// @lc code=start
class Solution1 {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size( ) > magazine.size( )) {
            return false;
        }

        int alphaCounts[26] = {0};


        for (auto &ch : magazine) {
            ++alphaCounts[ch - 'a'];
        }

        for (auto &ch : ransomNote) {
            if (alphaCounts[ch - 'a'] == 0) {
                return false;
            }
            --alphaCounts[ch - 'a'];
        }
        return true;
    }
};


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.size( ) > magazine.size( )) {
            return false;
        }
        sort(ransomNote.begin( ), ransomNote.end( ));
        sort(magazine.begin( ), magazine.end( ));
        size_t indexR = 0;
        size_t indexM = 0;


        for (;;) {
            char tmp = magazine[indexM];
            if (tmp > ransomNote[indexR]) {
                return false;

            } else if (tmp == ransomNote[indexR]) {
                    if (++indexR == ransomNote.size( )) {
                        return true;
                    }
                    if (++indexM == magazine.size( )) {
                        return false;
                    }
            }else {
                while (++indexM < magazine.size( ) && magazine[indexM] == tmp)
                    ;

                if (indexM == magazine.size( )) {
                    return false;
                }
            }
        }
    }
};

int main( ) {
    string   ransomNote = "fihjjjjei";
    string   magazine = "hjibagacbhadfaefdjaeaebgi";
    Solution solution;
    solution.canConstruct(ransomNote, magazine);
}

// @lc code=end


/*
// @lcpr case=start
// "a"\n"b"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"ab"\n
// @lcpr case=end

// @lcpr case=start
// "aa"\n"aab"\n
// @lcpr case=end

 */
