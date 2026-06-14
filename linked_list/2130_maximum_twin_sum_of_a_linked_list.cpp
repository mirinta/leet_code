#include <algorithm>

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
 * In a linked list of size "n", where "n" is even, the "i"th node (0-indexed) of the linked list is
 * known as the twin of the "(n-1-i)"th node, if 0 <= i <= (n / 2) - 1.
 *
 * - For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2.
 * There are the only nodes with twins for n = 4.
 *
 * The twin sum is defined as the sum of a node and its twn.
 *
 * Given the "head" of a linked list with even length, return the maximum twn sum of the linked
 * list.
 *
 * ! The number of nodes in the list is an even integer in the range [2, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    int pairSum(ListNode* head)
    {
        auto* last = reverse(getMiddle(head));
        int result = 0;
        while (last) {
            result = std::max(result, head->val + last->val);
            head = head->next;
            last = last->next;
        }
        return result;
    }

private:
    ListNode* getMiddle(ListNode* head)
    {
        if (!head)
            return nullptr;

        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

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
