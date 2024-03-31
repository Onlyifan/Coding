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

// 愚蠢
class Solution0 {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        bool hasMultiplyZero = false;
        int product = 1;
        vector<int>::iterator zeroIndex;
        for (auto it = nums.begin( ); it != nums.end( ); ++it) {
            if (0 == *it) {
                if (hasMultiplyZero) {
                    fill(nums.begin( ), nums.end( ), 0);
                    return nums;
                }
                zeroIndex = it;
                hasMultiplyZero = true;
            } else {
                product *= *it;
            }
        }

        if (hasMultiplyZero) {
            fill(nums.begin( ), nums.end( ), 0);
            *zeroIndex = product;
            return nums;
        }

        for (int &num : nums) {
            num = product / num;
        }
        return nums;
    }
};


// 还是愚蠢
class Solution00 {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        bool hasMultiplyZero = false;
        vector<int>::iterator zeroIndex;
        fill(_factors.begin( ), _factors.end( ), 1);

        for (auto it = nums.begin( ); it != nums.end( ); ++it) {
            if (0 == *it) {
                if (hasMultiplyZero) {
                    fill(nums.begin( ), nums.end( ), 0);
                    return nums;
                }
                hasMultiplyZero = true;
                zeroIndex = it;
            } else {
                _factors[abs(*it) - 1] *= *it;
            }
        }

        int product = 1;
        for (const auto &factor : _factors) {
            product *= factor;
        }

        if (hasMultiplyZero) {
            fill(nums.begin( ), nums.end( ), 0);
            *zeroIndex = product;
            return nums;
        }


        for (int i = 0; i != 30; ++i) {
            _factors[i] = product / (i + 1);
        }


        for (int &num : nums) {
            if (num > 0) {
                num = _factors[num - 1];
            } else {
                num = -_factors[abs(num) - 1];
            }
        }
        return nums;
    }

  private:
    array<long long, 30> _factors;
};

// 还是愚蠢
class Solution000 {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        for (int i = 0; i != nums.size( ); ++i) {
            ++_factors[nums[i]];
        }

        if (_factors[30] > 1) {
            fill(nums.begin( ), nums.end( ), 0);
            return nums;
        }

        int product = 1;
        for (int i = 0; i != 30; ++i) {
            product *= pow(i - 30, _factors[i]);
        }

        for (int i = 32; i != 61; ++i) {
            product *= pow(i - 30, _factors[i]);
        }

        if (_factors[30] == 1) {
            for (int i = 0; i != nums.size( ); ++i) {
                nums[i] = ((nums[i] == 0) ? product : 0);
            }
            return nums;
        }

        for (int i = 0; i != 30; ++i) {
            _factors[i] = product / (i - 30);
        }

        for (int i = 31; i != 61; ++i) {
            _factors[i] = product / (i - 30);
        }


        for (int &num : nums) {
            num = _factors[num + 30];
        }
        return nums;
    }

  private:
    array<int, 61> _factors;
};

// 愚蠢三号
class Solution0000 {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        array<int, 31> factor;
        vector<int> result(nums.size( ));

        int zeroIndex = -1;
        int product = 1;
        for (int i = 0; i != nums.size( ); ++i) {
            if (nums[i] == 0) {
                if (zeroIndex != -1) {
                    return result;
                }
                zeroIndex = i;
            } else {
                product *= nums[i];
            }
        }

        if (zeroIndex != -1) {
            result[zeroIndex] = product;
            return result;
        }

        for (int i = 1; i != 31; ++i) {
            factor[i] = product / i;
        }

        for (int &num : nums) {
            if (num > 0) {
                num = factor[num];
            } else {
                num = -factor[abs(num)];
            }
        }
        return nums;
    }
};


class Solution {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        vector<int> result(nums.size( ));
        int product = nums.front( );
        for (int i = 1; i != nums.size( ); ++i) {
            int tmp = nums[i];
            result[i] = product;
            product *= tmp;
        }

        product = nums.back( );
        result.front( ) = 1;
        for (int i = nums.size( ) - 2; i != -1; --i) {
            int tmp = nums[i];
            result[i] *= product;
            product *= tmp;
        }

        return result;
    }
};
