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
 * You are given two non-empty linked lists representing two non-negative integers. The most
 * significant digit comes first and each of their nods contains a single digit. Add the two numbers
 * and return the sum as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * ! The number of nodes in each linked list is in the range [1, 100].
 * ! 0 <= Node.val <= 9
 * ! It is guaranteed that the list represents a number that does not have leading zeros.
 */

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        auto* head1 = reverse(l1);
        auto* head2 = reverse(l2);
        ListNode vHead(-1);
        auto* node = &vHead;
        int carry = 0;
        while (head1 || head2) {
            const int val1 = head1 ? head1->val : 0;
            const int val2 = head2 ? head2->val : 0;
            const int sum = val1 + val2 + carry;
            node->next = new ListNode(sum % 10);
            carry = sum / 10;
            node = node->next;
            head1 = head1 ? head1->next : nullptr;
            head2 = head2 ? head2->next : nullptr;
        }
        if (carry > 0) {
            node->next = new ListNode(carry);
        }
        return reverse(vHead.next);
    }

private:
    ListNode* reverse(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode* prev = nullptr;
        auto* curr = head;
        while (curr) {
            auto* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
