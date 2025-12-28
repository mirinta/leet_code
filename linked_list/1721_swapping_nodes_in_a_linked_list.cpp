#include <utility>

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
 * You are given the "head" of a linked list, and an integer "k".
 *
 * Return the head of the linked list after swapping the values of the "k"th node from the beginning
 * and the "k"th node from the end (the list is 1-indexed).
 *
 * ! The number of nodes in the list is "n".
 * ! 1 <= k <= n
 */

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k)
    {
        if (!head || k < 1)
            return nullptr;
        //             A         B
        // index: 0    1    2    3    4    5
        // nodes: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
        auto* nodeA = head;
        while (--k) {
            nodeA = nodeA->next;
        }
        auto* iter = nodeA->next;
        auto* nodeB = head;
        while (iter) {
            iter = iter->next;
            nodeB = nodeB->next;
        }
        std::swap(nodeA->val, nodeB->val);
        return head;
    }
};