#include <unordered_map>

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
 * Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to
 * 0 until there are no such sequences.
 *
 * After doing so, return the head of the final linked list.  You may return any such answer.
 *
 * ! The given linked list will contain between 1 and 1000 nodes.
 * ! Each node in the linked list has -1000 <= node.val <= 1000.
 */

class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode vHead(0);
        vHead.next = head;
        std::unordered_map<int, ListNode*> map;
        int sum = 0;
        for (auto node = &vHead; node; node = node->next) {
            sum += node->val;
            map[sum] = node;
        }
        sum = 0;
        for (auto node = &vHead; node; node = node->next) {
            sum += node->val;
            node->next = map[sum]->next;
        }
        return vHead.next;
    }
};