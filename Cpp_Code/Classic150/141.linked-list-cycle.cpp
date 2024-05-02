/*
 * @lc app=leetcode.cn id=141 lang=cpp
 * @lcpr version=30122
 *
 * [141] 环形链表
 */


// @lcpr-template-start
using namespace std;
// @lcpr-template-end
// @lc code=start

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x)
        : val(x)
        , next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr) {
            return false;
        }

        ListNode *fast = head;
        ListNode *slow = head;

        do {
            fast = fast->next;
            if (!fast) {
                return false;
            }
            fast = fast->next;
            if (!fast) {
                return false;
            }

            slow = slow->next;
        } while (slow != fast);

        return true;
    }
};
// @lc code=end


/*
// @lcpr case=start
// [3,2,0,-4]\n1\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [1]\n-1\n
// @lcpr case=end

 */
