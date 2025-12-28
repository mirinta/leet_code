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
 * You are given the head of a linked list. Delete the middle node, and return the head of the
 * modified linked list.
 *
 * The middle node of a linked list of size n is the ⌊n / 2⌋th node from the start using 0-based
 * indexing, where ⌊x⌋ denotes the largest integer less than or equal to x.
 *
 * - For n = 1, 2, 3, 4, and 5, the middle nodes are 0, 1, 1, 2, and 2, respectively.
 *
 * ! The number of nodes in the list is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* slow = &vHead;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return vHead.next;
    }
};