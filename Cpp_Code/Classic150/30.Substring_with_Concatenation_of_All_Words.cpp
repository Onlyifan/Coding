#include <leetcode.h>
using namespace std;


// 重复次数太多了
class Solution1 {
  public:
    vector<int> findSubstring(string s, vector<string> &words) {
        unordered_map<string, int> wordMap;
        for (auto &w : words) {
            ++wordMap[w];
        }

        int wordSize = words[0].size( );

        int legalSize = s.size( ) - wordSize * words.size( );

        vector<int> result;
        for (int i = 0; i <= legalSize; ++i) {

            unordered_map<string, int> wordMap(wordMap);

            int j = 0;
            for (; j != words.size( ); ++j) {
                auto it = wordMap.find(s.substr(i + j * wordSize, wordSize));

                if (it == wordMap.end( ) || it->second == 0) {
                    break;
                }
                --it->second;
            }

            if (j == words.size( )) {
                result.emplace_back(i);
            }
        }


        return result;
    }
};


class Solution {
  public:
    vector<int> findSubstring(string s, vector<string> &words) {
        vector<int> result;

        int wordSize = words[0].size( );
        int totalSize = wordSize * words.size( );

        unordered_map<string, int> wordMap(words.size( ) << 2);
        for (auto &w : words) {
            ++wordMap[w];
        }

        for (int i = 0; i != wordSize; ++i) {

            int left = i;
            int right = i;


            for (;;) {
                if (right + wordSize > s.size( )) {
                    break;
                }

                auto it = wordMap.find(s.substr(right, wordSize));

                if (it == wordMap.end( )) {
                    while (left != right) {
                        ++wordMap[s.substr(left, wordSize)];
                        left += wordSize;
                    }
                    right += wordSize;
                    left = right;
                    continue;
                }

                while (it->second == 0) {
                    ++wordMap[s.substr(left, wordSize)];
                    left += wordSize;
                }

                --wordMap[s.substr(right, wordSize)];
                right += wordSize;

                if (right - left == totalSize) {
                    result.emplace_back(left);
                    ++wordMap[s.substr(left, wordSize)];
                    left += wordSize;
                }
            }

            while (left != right) {
                ++wordMap[s.substr(left, wordSize)];
                left += wordSize;
            }
        }

        return result;
    }
};
