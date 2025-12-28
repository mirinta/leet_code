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
 * Given the head of a linked list containing k distinct elements, return the head to a linked list
 * of length k containing the frequency of each distinct element in the given linked list in any
 * order.
 *
 * ! The number of nodes in the list is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    ListNode* frequenciesOfElements(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::unordered_map<int, int> map;
        for (auto* iter = head; iter; iter = iter->next) {
            map[iter->val]++;
        }
        ListNode vHead(-1);
        auto* node = &vHead;
        for (const auto& [val, freq] : map) {
            node->next = new ListNode(freq);
            node = node->next;
        }
        return vHead.next;
    }
};