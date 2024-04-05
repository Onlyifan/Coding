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
    string longestCommonPrefix(vector<string> &strs) {
        string result(strs.front( ));
        int maxSize = result.size( );
        if (0 == maxSize) {
            return result;
        }
        for (int i = 1; i != strs.size( ); ++i) {
            if (0 == strs[i].size( ) || strs[i][0] != result.front( )) {
                cout << result.front( ) << endl;
                cout << "??" << endl;
                return string( );
            }

            for (int j = 1; j < maxSize; ++j) {
                if (result[j] != strs[i][j]) {
                    maxSize = j;
                    break;
                }
            }
        }
        return result.substr(0, maxSize);
    }
};

int main( ) {
    Solution s1;
    vector<string> v{"", "abc", "cc"};
    cout << "\"" << s1.longestCommonPrefix(v) << "\"" << endl;
}
