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

// 排序？等通知吧你
class Solution1 {
  public:
    int hIndex(vector<int> &citations) {
        sort(citations.begin( ), citations.end( ), std::greater<int>( ));
        for (short i = citations.size( ) - 1; i != -1; --i) {
            if (citations[i] > i) {
                return i + 1;
            }
        }
        return 0;
    }
};

// 计数排序
class Solution2 {
  public:
    int hIndex(vector<int> &citations) {
        vector<int> hCounts(1 + citations.size( ));
        for (const auto &hindex : citations) {
            if (hindex < citations.size( )) {
                ++hCounts[hindex];
            } else {
                ++hCounts.back( );
            }
        }

        int accumulation = 0;

        for (int i = citations.size( ); i != 0; --i) {
            accumulation += hCounts[i];
            if (accumulation >= i) {
                return i;
            }
        }
        return 0;
    }
};


// 二分查找 *****

class Solution {
  public:
    int hIndex(vector<int> &citations) {

        int left = 0;
        int right = citations.size( );

        for (;;) {
            // 这里一定要 + 1，不然hIndex最后会恒等于left，死循环了
            int hIndex = (right + left + 1) >> 1;

            int count = 0;
            for (const int &c : citations) {
                if (c >= hIndex) {
                    ++count;
                }
            }

            if (hIndex == count) {
                return hIndex;
            }

            if (hIndex < count) {
                left = hIndex;
            } else {
                right = hIndex - 1;
            }

            if (left == right) {
                return left;
            }
        }
    }
};
