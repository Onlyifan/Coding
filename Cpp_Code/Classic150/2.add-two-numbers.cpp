/*
 * @lc app=leetcode.cn id=2 lang=cpp
 * @lcpr version=30122
 *
 * [2] 两数相加
 */


// @lcpr-template-start
#include <array>
using namespace std;
// @lcpr-template-end
// @lc code=start
struct ListNode {
    int val;
    ListNode *next;
    ListNode( )
        : val(0)
        , next(nullptr) {}
    ListNode(int x)
        : val(x)
        , next(nullptr) {}
    ListNode(int x, ListNode *next)
        : val(x)
        , next(next) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        bool carriedFlag = false;

        ListNode *tail;
        ListNode *result = l1;

        while (l1) {
            // 如果l2到底了
            if (nullptr == l2) {
                // 如果有进位
                if (carriedFlag) {
                    ++l1->val;

                } else {
                    break;
                }

            } else {
                l1->val += carriedFlag + l2->val;
                l2 = l2->next;
            }

            carriedFlag = l1->val / 10;
            l1->val %= 10;


            if (nullptr == l1->next) {
                if (l2 == nullptr) {
                    tail = l1;
                    break;
                }else {
                    l1->next = l2;
                    l2  = nullptr;
                }
            }

            l1 = l1->next;

        }

        if (carriedFlag) {
            tail->next = new ListNode(1);
        }

        return result;
    }
};
// @lc code=end


/*
// @lcpr case=start
// [2,4,3]\n[5,6,4]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n[0]\n
// @lcpr case=end

// @lcpr case=start
// [9,9,9,9,9,9,9]\n[9,9,9,9]\n
// @lcpr case=end

 */
