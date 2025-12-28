#include <stack>

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
 * Given the "head" of a singly linked list and two integers "left" and "right" where "left" <=
 * "right", reverse the nodes of the list from position "left" to position "right", and return the
 * reversed list.
 *
 * ! The number of nodes in the list is n.
 * ! 1 <= n <= 500
 * ! -500 <= Node.val <= 500
 * ! 1 <= left <= right <= n
 */

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        return approach2(head, left, right);
    }

private:
    // time O(N), space O(1)
    ListNode* approach2(ListNode* head, int left, int right)
    {
        if (!head)
            return nullptr;

        ListNode vHead(-1);
        vHead.next = head;
        auto* prev = &vHead;
        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }
        auto* beforeLeft = prev;
        auto* leftNode = beforeLeft->next;
        auto* curr = prev->next;
        for (int i = left; i <= right; ++i) {
            auto* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        } // when the loop ends, prev = rightNode, curr = rightNode->next
        leftNode->next = curr;
        beforeLeft->next = prev;
        return vHead.next;
    }

    // stack, time O(N), space O(N)
    ListNode* approach1(ListNode* head, int left, int right)
    {
        if (!head)
            return nullptr;

        // ...->prev->[LEFT->...->RIGHT]->next...
        ListNode vHead(-1);
        vHead.next = head;
        auto* prev = &vHead;
        for (int i = 0; i < left - 1; ++i) {
            prev = prev->next;
        }
        auto* node = prev->next;
        std::stack<ListNode*> stack;
        for (int i = left; i <= right; ++i) {
            auto* next = node->next;
            node->next = nullptr;
            stack.push(node);
            node = next;
        }
        while (!stack.empty()) {
            prev->next = stack.top();
            stack.pop();
            prev = prev->next;
        }
        prev->next = node;
        return vHead.next;
    }
};
