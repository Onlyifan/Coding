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

// no soertedNum
class Solution {
  public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        map<int, int> numMap;

        for (const auto &num : nums) {
            ++numMap[num];
        }

        vector<vector<int>> result;

        for (auto &elem : numMap) {
            if (elem.second == 1) {
                continue;
            }

            if (numMap.count(-2 * elem.first)) {
                if (elem.first == 0) {
                    if (elem.second > 2) {
                        result.push_back({0, 0, 0});
                    }
                    continue;
                }
                result.push_back({elem.first, elem.first, -2 * elem.first});
            }
        }


        for (auto it = numMap.begin( ); it != numMap.end( );) {
            int fixNum = it->first;

            auto left = ++it;
            auto right = numMap.end( );


            while (left != right) {
                auto tmp = right;
                --tmp;
                int sum = left->first + fixNum + tmp->first;
                if (sum == 0) {
                    result.push_back({left->first, tmp->first, fixNum});
                    ++left;
                    --right;
                    continue;
                } else if (sum > 0) {
                    --right;
                } else {
                    ++left;
                }
            }
        }


        return result;
    }
};


class Solution001 {
  public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        map<int, int> numMap;

        for (const auto &num : nums) {
            ++numMap[num];
        }

        vector<vector<int>> result;
        vector<int> sortedNums;
        sortedNums.reserve(numMap.size( ));

        for (auto &elem : numMap) {

            sortedNums.push_back(elem.first);
            if (elem.second == 1) {
                continue;
            }

            if (numMap.count(-2 * elem.first)) {
                if (elem.first == 0) {
                    if (elem.second > 2) {
                        result.push_back({0, 0, 0});
                    }
                    continue;
                }

                result.push_back({elem.first, elem.first, -2 * elem.first});
            }
        }


        for (int i = 0; i + 2 < sortedNums.size( ); ++i) {
            int left = i + 1;
            int right = sortedNums.size( ) - 1;


            while (left < right) {
                int sum = sortedNums[i] + sortedNums[left] + sortedNums[right];
                if (sum == 0) {
                    result.push_back({sortedNums[left++], sortedNums[i], sortedNums[right--]});
                    continue;
                } else if (sum > 0) {
                    --right;
                } else {
                    ++left;
                }
            }
        }


        return result;
    }
};


class Solution1212 {
  public:
    vector<vector<int>> threeSum(vector<int> &nums) {

        vector<vector<int>> result;
        sort(nums.begin( ), nums.end( ));


        for (int i = 0; i + 2 < nums.size( );) {

            if (nums[i] > 0) {
                break;
            }

            int left = i + 1;
            int right = nums.size( ) - 1;


            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[left], nums[i], nums[right]});
                    biggerIndex(nums, left);
                    smallerIndex(nums, right);
                    continue;
                } else if (sum > 0) {
                    smallerIndex(nums, right);
                } else {
                    biggerIndex(nums, left);
                }
            }

            biggerIndex(nums, i);
        }


        return result;
    }

    void biggerIndex(const vector<int> &nums, int &index) {
        int num = nums[index];
        do {
            ++index;
        } while (nums.size( ) != index && num == nums[index]);
    }


    void smallerIndex(const vector<int> &nums, int &index) {
        int num = nums[index];
        do {
            --index;
        } while (-1 != index && num == nums[index]);
    }
};
