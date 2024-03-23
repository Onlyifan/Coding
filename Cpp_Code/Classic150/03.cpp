#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Solution1 {
  public:
    int removeDuplicates(vector<int> &nums) {
        if (nums.size( ) == 0) {
            return 0;
        }

        for (int i = nums.size( ) - 2; i >= 0; --i) {
            nums[i + 1] ^= nums[i];
        }

        int newSize = 1;
        for (int i = 1; i < nums.size( ); ++i) {
            if (nums[i] != 0) {
                nums[newSize] = nums[newSize - 1] ^ nums[i];
                ++newSize;
            }
        }

        return newSize;
    }
};


class Solution {
  public:
    int removeDuplicates(vector<int> &nums) {
        if (nums.size( ) == 0) {
            return 0;
        }

        int currentIndex = 0;
        int currentNum = nums[0];

        for (auto &num : nums) {
            if (num != currentNum) {
                currentNum = num;
                nums[++currentIndex] = currentNum;
            }
        }

        return currentIndex + 1;
    }
};
