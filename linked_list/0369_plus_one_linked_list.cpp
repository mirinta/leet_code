#include <stack>

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
 * Given a non-negative integer represented as a linked list of digits, plus one to the integer.
 *
 * The digits are stored such that the most significant digit is at the head of the list.
 *
 * ! The number of nodes in the linked list is in the range [1, 100].
 * ! 0 <= Node.val <= 9
 * ! The number represented by the linked list does not contain leading zeros except for the zero
 * ! itself.
 */

class Solution {
public:
    ListNode* plusOne(ListNode* head)
    {
        std::stack<ListNode*> stack;
        auto* node = head;
        while (node) {
            stack.push(node);
            node = node->next;
        }
        int carry = 1;
        while (!stack.empty()) {
            const int sum = stack.top()->val + carry;
            stack.top()->val = sum % 10;
            carry = sum / 10;
            stack.pop();
        }
        if (carry > 0) {
            auto* newHead = new ListNode(carry);
            newHead->next = head;
            return newHead;
        }
        return head;
    }
};
