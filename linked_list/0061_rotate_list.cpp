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
 * Given the "head" of a linked list, rotate the list to the right by k places.
 *
 * ! The number of nodes in the list is in the range [0, 500].
 * ! -100 <= Node.val <= 100
 * ! 0 <= k <= 2 * 10^9
 */

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (!head || k <= 0)
            return head;

        // before: HEAD->...->NEW_TAIL(Xk+1)->Xk->...->TAIL(X1)
        //  after: Xk->...->TAIL(X1)->HEAD->...->NEW_TAIL(Xk+1)
        int count = 1;
        auto* tail = head;
        while (tail && tail->next) {
            tail = tail->next;
            count++;
        }
        if (count == 1 || k % count == 0)
            return head;

        k = k % count;
        auto* newTail = head;
        for (int i = 0; i < count - (k + 1); ++i) {
            newTail = newTail->next;
        }
        auto* newHead = newTail->next;
        newTail->next = nullptr;
        tail->next = head;
        return newHead;
    }
};
