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
    int trap(vector<int> &height) {
        int leftIndex = -1;
        int rightIndex = height.size( );
        int leftHeight = -1;
        int rightHeight = -1;

        int sum = 0;

        while (leftIndex != rightIndex) {
            if (leftHeight <= rightHeight) {
                ++leftIndex;

                if (leftHeight > height[leftIndex]) {

                    sum += leftHeight - height[leftIndex];
                } else {
                    leftHeight = height[leftIndex];
                }
            } else {
                --rightIndex;

                if (rightHeight > height[rightIndex]) {

                    sum += rightHeight - height[rightIndex];
                } else {
                    rightHeight = height[rightIndex];
                }
            }
        }

        return sum;
    }
};
