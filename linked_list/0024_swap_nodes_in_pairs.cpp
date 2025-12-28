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
 * Given a linked list, swap every two adjacent nodes and return its head. You must solve the
 * problem without modifying the values in the lits's nodes (i.e., only nodes themselves may be
 * changed.)
 *
 * ! The number of nodes in the list is in the range [0, 100].
 * ! 0 <= Node.val <= 100
 */

class Solution {
public:
    ListNode* swapPairs(ListNode* head)
    {
        return approach1(head);
    }

private:
    ListNode* approach2(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        auto* next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }

    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        ListNode vHead(-1);
        auto* node = &vHead;
        auto* curr = head;
        while (curr && curr->next) {
            auto* next = curr->next;
            auto* nextNext = next->next;
            node->next = next;
            next->next = curr;
            curr->next = nextNext;
            node = curr;
            curr = nextNext;
        }
        return vHead.next;
    }
};
