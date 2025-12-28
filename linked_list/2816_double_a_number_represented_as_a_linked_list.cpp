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
 * You are given the head of a non-empty linked list representing a non-negative integer without
 * leading zeroes.
 *
 * Return the head of the linked list after doubling it.
 *
 * ! The number of nodes in the list is in the range [1, 10^4]
 * ! 0 <= Node.val <= 9
 * ! The input is generated such that the list represents a number that does not have leading zeros,
 * ! except the number 0 itself.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* doubleIt(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        auto* node = &vHead;
        auto* curr = reverse(head);
        int carry = 0;
        while (curr) {
            const int sum = 2 * curr->val + carry;
            node->next = new ListNode(sum % 10);
            carry = sum / 10;
            curr = curr->next;
            node = node->next;
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