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

// 循环
class Solution1 {
  public:
    string convert(string s, int numRows) {
        if (1 == numRows) {
            return s;
        }

        int numV = (numRows - 1) << 1;
        int strPart = (s.size( ) - 1) / numV;
        int left = s.size( ) - strPart * numV;

        string result;

        for (int i = 0; i <= numV * strPart;) {
            result.push_back(s[i]);
            i += numV;
        }

        int rowNum = 1;
        for (; rowNum != numRows - 1; ++rowNum) {
            int i = 0;
            for (; i != numV * strPart;) {
                result.push_back(s[i + rowNum]);
                i += numV;
                result.push_back(s[i - rowNum]);
            }

            if (rowNum < left) {
                result.push_back(s[i + rowNum]);
                if (numV - rowNum < left) {
                    result.push_back(s[i + numV - rowNum]);
                }
            }
        }

        int i = 0;
        for (; i != numV * strPart;) {

            result.push_back(s[i + rowNum]);
            i += numV;
        }


        if (numRows <= left) {
            result.push_back(s[i + rowNum]);
        }

        return result;
    }
};

class Solution {
  public:
    string convert(string s, int numRows) {
        if (1 == numRows) {
            return s;
        }

        vector<string> sortedAlpha(numRows);

        int flag = -1;
        int index = 0;

        int i = 0;
        for (; i != s.size( ); ++i) {
            if (index == 0 || index == numRows - 1) {
                flag = -flag;
            }

            sortedAlpha[index].push_back(s[i]);
            index += flag;
        }

        return accumulate(sortedAlpha.begin( ), sortedAlpha.end( ), string( ));
    }
};
