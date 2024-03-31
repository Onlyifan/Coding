#include <algorithm>
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>
using namespace std;


class Solution {
  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {

        int wordSize = beginWord.size( );

        auto endWordIt = find(wordList.begin( ), wordList.end( ), endWord);
        if (endWordIt == wordList.end( )) {
            return 0;
        }

        int endIndex = endWordIt - wordList.begin( );

        unordered_map<string, set<int>> wordPart;
        wordPart.reserve(wordSize << 6);

        for (int i = 0; i != wordList.size( ); ++i) {
            for (int j = 0; j != wordSize; ++j) {
                string tmp = wordList[i];
                tmp[j] = '\0';
                wordPart[tmp].emplace(i);
            }
        }

        queue<pair<string, int>, list<pair<string, int>>> pathStr;
        pathStr.emplace(pair<string, int>{beginWord, 2});
        unordered_set<int> visitedIndex;
        // visitedIndex.reserve(wordList.size( ) << 2);
        while (!pathStr.empty( )) {
            string topWord = pathStr.front( ).first;
            int count = pathStr.front( ).second;
            pathStr.pop( );

            for (int i = 0; i != wordSize; ++i) {
                string tmp = topWord;
                tmp[i] = '\0';

                // 查找 dog 的 d*g
                auto it = wordPart.find(tmp);
                if (it == wordPart.end( )) {
                    continue;
                }

                // 如果找到了终点
                if (it->second.count(endIndex)) {
                    return count;
                }

                // 遍历所有的 d*g
                for (const int &num : it->second) {

                    // 如果是新的，就添加到已遍历SET,
                    if (!visitedIndex.count(num)) {
                        pathStr.emplace(pair<string, int>(wordList[num], count + 1));
                        visitedIndex.emplace(num);
                    }
                }
            }
        }

        return 0;
    }
};


class Solution1 {
  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {

        int wordSize = beginWord.size( );

        unordered_map<string, unordered_set<string>> wordPart;
        wordPart.reserve(wordSize << 6);

        for (int i = 0; i != wordList.size( ); ++i) {
            for (int j = 0; j != wordSize; ++j) {
                string tmp = wordList[i];
                tmp[j] = '\0';
                wordPart[tmp].emplace(wordList[i]);
            }
        }

        queue<pair<string, int>, list<pair<string, int>>> pathStr;
        pathStr.emplace(make_pair(beginWord, 0));
        unordered_set<string> visitedIndex;

        while (!pathStr.empty( )) {
            string topWord = pathStr.front( ).first;
            int count = pathStr.front( ).second + 1;
            pathStr.pop( );

            for (int i = 0; i != wordSize; ++i) {
                string tmp = topWord;
                tmp[i] = '\0';

                // 查找 dog 的 d*g
                auto it = wordPart.find(tmp);
                if (it == wordPart.end( )) {
                    continue;
                }

                // 如果找到了终点
                if (it->second.count(endWord)) {
                    return count + 1;
                }

                // 遍历所有的 d*g
                for (const string &num : it->second) {
                    // 如果是新的，就添加到已遍历SET,

                    if (!visitedIndex.count(num)) {
                        pathStr.emplace(make_pair(num, count));
                        visitedIndex.emplace(num);
                    }
                }
            }
        }

        return 0;
    }
};
