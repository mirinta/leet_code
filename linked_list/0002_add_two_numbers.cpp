/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * You are given two non-empty linked lists representing two non-negative integers. The digits are
 * stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and
 * return the sum as a linked list.
 *
 * You make assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * ! The number of nodes in each linked list is in the range [1, 100].
 * ! 0 <= Node.val <= 9
 * ! It is guaranteed that the list represents a number that does not have leading zeros.
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode vHead(-1);
        auto* i = l1;
        auto* j = l2;
        auto* k = &vHead;
        int carry = 0;
        while (i || j) {
            const int val1 = i ? i->val : 0;
            const int val2 = j ? j->val : 0;
            const int sum = val1 + val2 + carry;
            k->next = new ListNode(sum % 10);
            carry = sum / 10;
            k = k->next;
            if (i) {
                i = i->next;
            }
            if (j) {
                j = j->next;
            }
        }
        if (carry > 0) {
            k->next = new ListNode(carry);
        }
        return vHead.next;
    }
};
