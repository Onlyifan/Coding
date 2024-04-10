#include <leetcode.h>
using namespace std;


class Solution {
  public:
    string minWindow(string s, string t) {
        if (s.size( ) < t.size( )) {
            return "";
        }


        unordered_map<char, int> alphaMap;
        for (auto &ch : t) {
            ++alphaMap[ch];
        }


        int right = 0;
        int left = 0;
        int remainSize = t.size( );

        // length, index
        int resultLength = numeric_limits<int>::max( );
        int resultIndex;
        while (right != s.size( )) {
            auto it = alphaMap.find(s[right++]);
            if (it == alphaMap.end( )) {
                continue;
            }

            if (remainSize != 0) {
                if (--it->second >= 0) {
                    --remainSize;
                }
            }

            if (0 == remainSize) {
                remainSize = 1;
                while ((it = alphaMap.find(s[left])) == alphaMap.end( ) || ++it->second <= 0) {
                    ++left;
                }
                if (right - left < resultLength) {
                    resultLength = right - left;
                    resultIndex = left;
                }

                ++left;
            }
        }

        if (numeric_limits<int>::max( ) == resultLength) {
            return "";
        }
        return s.substr(resultIndex, resultLength);
    }
};
