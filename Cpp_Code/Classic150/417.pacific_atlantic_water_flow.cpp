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

// 最原始的BFS
struct PairHash {
    size_t operator( )(const pair<int, int> &p) const { return ((p.first | 1) << 4) ^ p.second; }
};

class Solution1 {
  public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
        int maxI = heights.size( ) - 1;
        int maxJ = heights[0].size( ) - 1;

        vector<vector<int>> result;
        for (int i = 0; i != heights.size( ); ++i) {
            for (int j = 0; j != heights[0].size( ); ++j) {

                stack<pair<int, int>> bfsStack;
                bfsStack.emplace(make_pair(i, j));
                unordered_set<pair<int, int>, PairHash> visitedLoc{{i, j}};

                pair<bool, bool> flow{false, false};
                while (!bfsStack.empty( )) {
                    pair<int, int> currentLoc = bfsStack.top( );
                    int &x = currentLoc.first;
                    int &y = currentLoc.second;
                    bfsStack.pop( );

                    if ((x == 0 || y == 0) && flow.first == false) {
                        flow.first = true;
                    }

                    if ((x == maxI || y == maxJ) && flow.second == false) {
                        flow.second = true;
                    }

                    if (flow.first == true && flow.second == true) {
                        result.emplace_back(vector<int>{i, j});
                        break;
                    }


                    if (x != 0 && !visitedLoc.count({x - 1, y}) &&
                        heights[x][y] >= heights[x - 1][y]) {
                        bfsStack.emplace(make_pair(x - 1, y));
                        visitedLoc.emplace(make_pair(x - 1, y));
                    }

                    if (y != 0 && !visitedLoc.count({x, y - 1}) &&
                        heights[x][y] >= heights[x][y - 1]) {
                        bfsStack.emplace(make_pair(x, y - 1));
                        visitedLoc.emplace(make_pair(x, y - 1));
                    }

                    if (x != maxI && !visitedLoc.count({x + 1, y}) &&
                        heights[x][y] >= heights[x + 1][y]) {
                        bfsStack.emplace(make_pair(x + 1, y));
                        visitedLoc.emplace(make_pair(x + 1, y));
                    }

                    if (y != maxJ && !visitedLoc.count({x, y + 1}) &&
                        heights[x][y] >= heights[x][y + 1]) {
                        bfsStack.emplace(make_pair(x, y + 1));
                        visitedLoc.emplace(make_pair(x, y + 1));
                    }
                }
            }
        }

        return result;
    }
};


class Solution {
  public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
        _maxFirst = heights.size( );
        _maxSecond = heights[0].size( );

        vector<vector<bool>> _pacific(_maxFirst, vector<bool>(_maxSecond));
        vector<vector<bool>> _atlantic(_maxFirst, vector<bool>(_maxSecond));

        for (int j = 0; j != _maxSecond; ++j) {
            dfs(heights, 0, j, _pacific);
            dfs(heights, _maxFirst - 1, j, _atlantic);
        }

        for (int i = 0; i != _maxFirst; ++i) {
            dfs(heights, i, 0, _pacific);
            dfs(heights, i, _maxSecond - 1, _atlantic);
        }

        vector<vector<int>> result;
        for (int i = 0; i != _maxFirst; ++i) {
            for (int j = 0; j != _maxSecond; ++j) {
                if (_pacific[i][j] == true && _atlantic[i][j] == true) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }

  private:
    bool inAera(const int &x, const int &y) const {
        return x >= 0 && x != _maxFirst && y >= 0 && y != _maxSecond;
    }
    void dfs(vector<vector<int>> &heights, int x, int y, vector<vector<bool>> &result) {
        if (result[x][y] == true) {
            return;
        }
        result[x][y] = true;


        for (const auto &vQuantity : _direction) {
            int newX = x + vQuantity[0];
            int newY = y + vQuantity[1];
            if (inAera(newX, newY) && heights[x][y] <= heights[newX][newY]) {
                dfs(heights, newX, newY, result);
            }
        }
    }


  private:
    int _direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int _maxFirst;
    int _maxSecond;
};
