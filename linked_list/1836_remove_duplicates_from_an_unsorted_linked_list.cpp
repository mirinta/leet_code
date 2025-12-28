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
 * Given the head of a linked list, find all the values that appear more than once in the list and
 * delete the nodes that have any of those values.
 *
 * Return the linked list after the deletions.
 *
 * ! The number of nodes in the list is in the range [1, 10^5]
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::unordered_map<int, int> map;
        for (auto* iter = head; iter; iter = iter->next) {
            map[iter->val]++;
        }
        ListNode vHead(-1);
        auto* curr = &vHead;
        while (head) {
            auto* next = head->next;
            head->next = nullptr;
            if (map[head->val] == 1) {
                curr->next = head;
                curr = curr->next;
            }
            head = next;
        }
        return vHead.next;
    }
};