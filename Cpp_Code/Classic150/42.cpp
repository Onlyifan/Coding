#include <leetcode.h>
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
