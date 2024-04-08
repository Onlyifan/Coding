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
    int maxArea(vector<int> &height) {
        int area = 0;
        int left = 0;
        int right = height.size( ) - 1;
        while (left < right) {
            int leftHeight = height[left];
            int rightHeight = height[right];
            if (leftHeight == rightHeight) {
                area = max(area, (right - left) * rightHeight);
                --right;
                ++left;
            } else if (leftHeight > rightHeight) {
                area = max(area, (right - left) * rightHeight);
                --right;
            } else {
                area = max(area, (right - left) * leftHeight);
                ++left;
            }
        }

        return area;
    }
};


class Solution_tmp {
  public:
    int maxArea(vector<int> &height) {
        int area = 0;
        int left = 0;
        int right = height.size( ) - 1;

        while (left < right) {
            int leftHeight = height[left];
            int rightHeight = height[right];
            if (leftHeight == rightHeight) {
                area = max(area, (right - left) * rightHeight);
                --right;
                ++left;
            } else if (leftHeight > rightHeight) {
                area = max(area, (right - left) * rightHeight);

                while (rightHeight >= height[--right])
                    ;

            } else {
                area = max(area, (right - left) * leftHeight);

                while (leftHeight >= height[++left])
                    ;
            }
        }

        return area;
    }
};


class Solution {
  public:
    int maxArea(vector<int> &height) {
        int area = 0;
        int left = 0;
        int right = height.size( ) - 1;
        while (left < right) {
            int leftHeight = height[left];
            int rightHeight = height[right];
            if (leftHeight > rightHeight) {
                area = max(area, (right - left) * rightHeight);

                while (rightHeight >= height[--right])
                    ;

            } else {
                area = max(area, (right - left) * leftHeight);

                while (leftHeight > height[++left])
                    ;
            }
        }

        return area;
    }
};
