/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Given the "head" of a linked list, return the node where the cycle begins. If there is no cycle,
 * return "nullptr".
 *
 * Do not modify the linked list.
 *
 * ! The number of the nodes in the list is in the range [0, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! pos is -1 or a valid index in the linked-list.
 */

class Solution {
public:
    ListNode* detectCycle(ListNode* head)
    {
        if (!head || !head->next)
            return nullptr;

        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }
        if (!fast || !fast->next)
            return nullptr; // no cycle

        // O is the head node
        // X is the node where the cycle begins
        // slow and fast meet at node M
        //
        // O -----> X ----> M
        //          |       |
        //          |       |
        //          B <---- A
        //
        // dist_fast = OX + XM + MA + AB + BX + XM = 2 * dist_slow
        // dist_slow = OX + XM
        // MA + AB + BX + XM = OX + XM => OX = MA + MA + BX
        slow = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};