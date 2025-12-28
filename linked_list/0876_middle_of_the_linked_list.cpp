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
 * Given the head of a singly linked list, return the middle node of the linked list.
 *
 * If there are two middle nodes, return the second middle node.
 *
 * ! The number of nodes in the list is in the range [1, 100].
 * ! 1 <= Node.val <= 100
 */

class Solution {
public:
    ListNode* middleNode(ListNode* head)
    {
        if (!head)
            return nullptr;

        auto* fast = head;
        auto* slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};
