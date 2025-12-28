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
 * You are given the head of a singly linked-list. The list can be represented as:
 *
 * L0 -> L1 -> ... -> Ln-1 -> Ln
 *
 * Reorder the list to be on the following form:
 *
 * L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...
 *
 * You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 *
 * ! The number of nodes in the list is in the range [1, 5 * 10^4].
 * ! 1 <= Node.val <= 1000
 */

class Solution {
public:
    void reorderList(ListNode* head)
    {
        if (!head)
            return;

        // before: HEAD->NEXT->...->MID<-...<-PREV<-TAIL
        //  after: HEAD->TAIL->NEXT->...->MID<-...<-PREV
        auto* middle = getMiddleNode(head);
        auto* tail = reverse(middle); // MID->next = nullptr
        while (tail->next) {
            auto* next = head->next;
            auto* prev = tail->next;
            head->next = tail;
            tail->next = next;
            head = next;
            tail = prev;
        }
    }

private:
    ListNode* getMiddleNode(ListNode* head)
    {
        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    ListNode* reverse(ListNode* head)
    {
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
