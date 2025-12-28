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
 * Given the head of a sorted linked list, delete all duplicates such that each element appears only
 * once. Return the linked list sorted as well.
 *
 * ! The number of nodes in the list is in the range [0, 300].
 * ! -100 <= Node.val <= 100
 * ! The list is guaranteed to be sorted in ascending order.
 */

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
            return nullptr;

        // duplicates are adjacent
        auto* keep = head;
        auto* curr = head;
        while (curr) {
            if (curr->val != keep->val) {
                keep->next = curr;
                keep = keep->next;
            }
            curr = curr->next;
        }
        keep->next = nullptr;
        return head;
    }
};
