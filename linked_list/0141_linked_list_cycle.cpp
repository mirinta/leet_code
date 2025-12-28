/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Given "head", the head of a linked list, determine if the linked list has a cycle in it.
 *
 * Return "true" if there is a cycle in the linked list. Otherwise, return "false".
 *
 * ! The number of the nodes in the list is in the range [0, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! pos is -1 or a valid index in the linked-list.
 */

class Solution {
public:
    bool hasCycle(ListNode* head)
    {
        if (!head)
            return false;

        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};
