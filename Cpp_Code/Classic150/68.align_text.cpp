#include <string>
#include <vector>
using namespace std;

// 愚蠢
class Solution1 {
  public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> result;

        int sumLength = 0;
        int start = 0;
        int end = 0;

        while (end != words.size( )) {
            sumLength += words[end].size( ) + 1;
            if (sumLength > maxWidth + 1) {
                int depart = end - start;

                result.emplace_back(words[start++]);

                if (1 == depart) {
                    result.back( ).append(maxWidth - words[start - 1].size( ), ' ');
                    sumLength = 0;
                    continue;
                }

                int spare = maxWidth - sumLength + 1 + words[end].size( ) + depart;

                int blankSize = spare / (depart - 1);
                int leftBlankCount = spare % (depart - 1);


                for (int i = 0; i != leftBlankCount; ++i) {
                    result.back( ).append(blankSize + 1, ' ');
                    result.back( ).append(words[start++]);
                }

                while (start != end) {
                    result.back( ).append(blankSize, ' ');
                    result.back( ).append(words[start++]);
                }

                sumLength = 0;
            } else {
                ++end;
            }
        }

        result.emplace_back(words[start]);
        maxWidth -= words[start++].size( );
        while (start != end) {
            result.back( ).push_back(' ');
            result.back( ) += words[start];
            maxWidth -= words[start++].size( ) + 1;
        }

        result.back( ).append(maxWidth, ' ');

        return result;
    }
};

class Solution {
  public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> result;

        int sumLength = 0;
        int start = 0;
        int end = 0;

        while (end != words.size( )) {
            if (sumLength + words[end].size( ) > maxWidth) {
                string tmp = words[start++];

                int depart = end - start;
                int spare = maxWidth - sumLength + depart + 1;

                if (0 == depart) {
                    tmp.append(spare, ' ');

                } else {
                    int blankSize = spare / depart + 1;

                    for (int i = 0; i != spare % depart; ++i) {
                        tmp.append(blankSize, ' ');
                        tmp += words[start++];
                    }

                    --blankSize;
                    while (start != end) {
                        tmp.append(blankSize, ' ');
                        tmp += words[start++];
                    }
                }

                result.emplace_back(tmp);
                sumLength = 0;

            } else {
                sumLength += words[end++].size( ) + 1;
            }
        }

        string tmp(words[start]);
        maxWidth -= tmp.size( );

        ++start;
        while (start != end) {
            tmp.push_back(' ');
            tmp += words[start];
            maxWidth -= words[start++].size( ) + 1;
        }

        tmp.append(maxWidth, ' ');
        result.emplace_back(tmp);

        return result;
    }
};
