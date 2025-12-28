#include <cmath>
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
 * Given the head of a singly linked list and an integer k, split the linked list into k consecutive
 * linked list parts.
 *
 * The length of each part should be as equal as possible: no two parts should have a size differing
 * by more than one. This may lead to some parts being null.
 *
 * The parts should be in the order of occurrence in the input list, and parts occurring earlier
 * should always have a size greater than or equal to parts occurring later.
 *
 * Return an array of the k parts.
 *
 * ! The number of nodes in the list is in the range [0, 1000].
 * ! 0 <= Node.val <= 1000
 * ! 1 <= k <= 50
 */

class Solution {
public:
    std::vector<ListNode*> splitListToParts(ListNode* head, int k)
    {
        std::vector<ListNode*> result(k);
        if (!head)
            return result;

        int numOfNodes = 0;
        for (auto* node = head; node; node = node->next) {
            numOfNodes++;
        }
        for (int i = 0; i < k && numOfNodes > 0; ++i) {
            ListNode vHead{-1};
            auto* node = &vHead;
            const int size = std::ceil(1.0 * numOfNodes / (k - i));
            for (int j = 0; j < size && head; ++j) {
                auto* next = head->next;
                head->next = nullptr;
                node->next = head;
                node = node->next;
                head = next;
                numOfNodes--;
            }
            result[i] = vHead.next;
        }
        return result;
    }
};