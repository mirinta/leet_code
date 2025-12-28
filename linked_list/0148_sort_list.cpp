#include <algorithm>
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
 * Given the head of a linked list, return the list after sorting it in ascending order.
 *
 * ! The number of nodes in the list is in the range [0, 5 * 10^4].
 * ! -10^5 <= Node.val <= 10^5
 */

class Solution {
public:
    ListNode* sortList(ListNode* head)
    {
        return approach2(head);
    }

private:
    // Merge sort, time O(NlogN), space O(logN)
    ListNode* approach2(ListNode* head)
    {
        if (!head || !head->next) // at least two nodes
            return head;

        // HEAD->...->prev->MID->...->TAIL
        // |<---part1--->|  |<--part2--->|
        auto* slow = head;
        auto* fast = head;
        ListNode* prev = nullptr;
        while (fast && fast->next) {
            prev = slow;
            fast = fast->next->next;
            slow = slow->next;
        }
        prev->next = nullptr;
        auto* left = approach2(head);
        auto* right = approach2(slow);
        return mergeTwoSortedLinkedLists(left, right);
    }

    ListNode* mergeTwoSortedLinkedLists(ListNode* list1, ListNode* list2)
    {
        if (!list1 && !list2)
            return nullptr;

        ListNode vHead(-1);
        auto* node = &vHead;
        auto* i1 = list1;
        auto* i2 = list2;
        while (i1 || i2) {
            if (!i1) {
                node->next = i2;
                i2 = i2->next;
            } else if (!i2) {
                node->next = i1;
                i1 = i1->next;
            } else if (i1->val < i2->val) {
                node->next = i1;
                i1 = i1->next;
            } else {
                node->next = i2;
                i2 = i2->next;
            }
            node = node->next;
        }
        return vHead.next;
    }

    // time O(NlogN), space O(N)
    ListNode* approach1(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::vector<ListNode*> nodes;
        auto* node = head;
        while (node) {
            nodes.push_back(node);
            auto* next = node->next;
            node->next = nullptr;
            node = next;
        }
        std::sort(nodes.begin(), nodes.end(), [](auto* n1, auto* n2) { return n1->val < n2->val; });
        for (int i = 0; i < nodes.size() - 1; ++i) {
            nodes[i]->next = nodes[i + 1];
        }
        return nodes.front();
    }
};