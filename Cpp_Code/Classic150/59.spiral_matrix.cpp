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


class Solution1 {
  public:
    vector<vector<int>> generateMatrix(int n) {

        int direction[4][2]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int x = 0;
        int y = -1;
        int count = n;
        int length = n;
        int directionIndex = 3;

        vector<vector<int>> matrix(n, vector<int>(n));

        for (int i = 1; i <= n * n; ++i) {
            if (count == length) {
                if (directionIndex == 3) {
                    // x += direction[directionIndex][0];
                    // y += direction[directionIndex][1];
                    // matrix[x][y] = i;
                    matrix[x][++y] = i;
                    length -= 2;
                    if (length < 0) {
                        break;
                    }
                    directionIndex = 0;
                } else {
                    x += direction[directionIndex][0];
                    y += direction[directionIndex][1];
                    matrix[x][y] = i;
                    ++directionIndex;
                }
                count = 0;
                continue;
            }

            ++count;
            x += direction[directionIndex][0];
            y += direction[directionIndex][1];
            matrix[x][y] = i;
        }

        return matrix;
    }
};
