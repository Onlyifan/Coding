#include <leetcode.h>
using namespace std;


class Solution {
  public:
    int lengthOfLongestSubstring(string s) {

        int maxLen = 0;
        int left = -1;
        int right = 0;
        array<bool, 123> alpha;
        while (right != s.size( )) {
            while (alpha[s[right]] == true) {
                alpha[s[--left]] = false;
            }


            alpha[s[right]] = true;
            maxLen = max(maxLen, right - left);
            ++right;
        }

        return maxLen;
    }
};
