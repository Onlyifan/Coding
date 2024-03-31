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
    int minMutation(string startGene, string endGene, vector<string> &bank) {

        auto endGeneIt = find(bank.begin( ), bank.end( ), endGene);
        if (endGeneIt == bank.end( )) {
            return -1;
        }

        int endIndex = endGeneIt - bank.begin( );

        unordered_map<string, set<int>> wordPart;

        for (int i = 0; i != bank.size( ); ++i) {
            for (int j = 0; j != 8; ++j) {
                string tmp = bank[i];
                tmp[j] = '\0';
                wordPart[tmp].emplace(i);
            }
        }

        queue<pair<string, int>, list<pair<string, int>>> pathStr;
        pathStr.emplace(pair<string, int>{startGene, 1});
        unordered_set<int> visitedIndex;
        // visitedIndex.reserve(bank.size( ) << 2);
        while (!pathStr.empty( )) {
            string topWord = pathStr.front( ).first;
            int count = pathStr.front( ).second;
            pathStr.pop( );

            for (int i = 0; i != 8; ++i) {
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
                        pathStr.emplace(make_pair(bank[num], count + 1));
                        visitedIndex.emplace(num);
                    }
                }
            }
        }

        return -1;
    }
};
