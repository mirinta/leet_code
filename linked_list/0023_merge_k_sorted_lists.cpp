#include <queue>
#include <vector>

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
 * You are given an array of "k" linked-lists "lists", each linked-list is sorted in ascending
 * order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * ! k == lists.length
 * ! 0 <= k <= 10^4
 * ! 0 <= lists[i].length <= 500
 * ! -10^4 <= lists[i][j] <= 10^4
 * ! lists[i] is sorted in ascending order.
 * ! The sum of lists[i].length will not exceed 10^4.
 */

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        if (lists.empty())
            return nullptr;

        auto comparator = [](auto* node1, auto* node2) { return node1->val > node2->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comparator)> pq(comparator); // min head
        for (auto* head : lists) {
            if (head) {
                pq.push(head);
            }
        }
        ListNode vHead(-1);
        auto* node = &vHead;
        while (!pq.empty()) {
            auto* top = pq.top();
            pq.pop();
            node->next = top;
            if (top->next) {
                pq.push(top->next);
            }
            node = node->next;
        }
        return vHead.next;
    }
};
