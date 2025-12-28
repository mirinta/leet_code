/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 给定两个用链表表示的整数，每个节点包含一个数位。
 *
 * 这些数位是反向存放的，也就是个位排在链表首部。
 *
 * 编写函数对这两个整数求和，并用链表形式返回结果。
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode vHead(-1);
        auto* node = &vHead;
        int carry = 0;
        while (l1 || l2) {
            const int val1 = l1 ? l1->val : 0;
            const int val2 = l2 ? l2->val : 0;
            const int sum = val1 + val2 + carry;
            carry = sum / 10;
            node->next = new ListNode(sum % 10);
            node = node->next;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            node->next = new ListNode(carry);
        }
        return vHead.next;
    }
};