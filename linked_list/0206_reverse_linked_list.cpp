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
 * Given the "head" of a singly linked list, reverse the list, and return the reversed list.
 *
 * ! The number of nodes in the list is the range [0, 5000].
 * ! -5000 <= Node.val <= 5000
 */

class Solution {
public:
    ListNode* reverseList(ListNode* head)
    {
        return approach2(head);
    }

private:
    ListNode* approach2(ListNode* head)
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

    ListNode* approach1(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        auto* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
