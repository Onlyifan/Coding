#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;


class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> diff;

        for (int i = 0; i != nums.size( ); ++i) {
            auto it = diff.find(nums[i]);
            if (it == diff.end( )) {
                diff.emplace(make_pair(target - nums[i], i));
            } else {
                return {i, it->second};
            }
        }

        return {0, 0};
    }
};
