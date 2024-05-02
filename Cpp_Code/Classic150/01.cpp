#include <algorithm>
#include <iostream>
#include <vector>
#include <Accelerate/Accelerate.h>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        if (n == 0) {
            return;
        }

        int current = n + m - 1;
        int index1 = m - 1;
        int index2 = n - 1;

        while (index1 >= 0 && index2 >= 0) {
            if (nums1[index1] > nums2[index2]) {
                nums1[current--] = nums1[index1--];
            } else {
                nums1[current--] = nums2[index2--];
            }
        }

        if (index1 >= 0) {
            return;
        }

        std::copy(nums2.begin( ), nums2.begin( ) + index2 + 1, nums1.begin( ));
    }
};

int main(void) {
    return 0;
}