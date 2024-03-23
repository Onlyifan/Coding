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

// 比较笨
class Solution1 {
  public:
    int maxProfit(vector<int> &prices) {
        int purchasePrice = numeric_limits<int>::max( );
        int sellPrice = -1;
        int totalProfit = 0;


        int i = 0;
        for (;;) {
            while (i < prices.size( ) && purchasePrice > prices[i]) {
                purchasePrice = prices[i];
                ++i;
            }
            while (i < prices.size( ) && sellPrice < prices[i]) {
                sellPrice = prices[i];
                ++i;
            }
            if (i >= prices.size( )) {
                return totalProfit;
            }
            totalProfit += sellPrice - purchasePrice;
            sellPrice = -1;
            purchasePrice = numeric_limits<int>::max( );

            ++i;
        }
        return totalProfit;
    }
};
// 动态规划
class Solution3 {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp[n][2];
        dp[0][0] = 0, dp[0][1] = -prices[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
        }
        return dp[n - 1][0];
    }
};

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int totalProfit = 0;
        for (int i = 1; i < prices.size( ); ++i) {
            totalProfit += max(0, prices[i] - prices[i - 1]);
        }


        return totalProfit;
    }
};
