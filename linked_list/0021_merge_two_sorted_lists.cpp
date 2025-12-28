#include <climits>

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
 * You are given the heads of two sorted linked lists "list1" and "list2".
 *
 * Merge the two lists in one sorted list. The list should be made by splicing together the nodes of
 * the first two lists.
 *
 * Return the head of the merged linked list.
 *
 * ! The number of nodes in both lists is in the range [0, 50].
 * ! -100 <= Node.val <= 100
 * ! Both list1 and list2 are sorted in non-decreasing order.
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        return approach1(list1, list2);
    }

private:
    ListNode* approach2(ListNode* list1, ListNode* list2)
    {
        if (!list1)
            return list2;

        if (!list2)
            return list1;

        if (list1->val < list2->val) {
            list1->next = approach2(list1->next, list2);
            return list1;
        }
        list2->next = approach2(list1, list2->next);
        return list2;
    }

    ListNode* approach1(ListNode* list1, ListNode* list2)
    {
        if (!list1 || !list2)
            return list1 ? list1 : list2;

        ListNode vHead(-1);
        auto* k = &vHead;
        auto* i = list1;
        auto* j = list2;
        while (i || j) {
            const int val1 = i ? i->val : INT_MAX;
            const int val2 = j ? j->val : INT_MAX;
            if (val1 < val2) {
                k->next = i;
                i = i->next;
            } else {
                k->next = j;
                j = j->next;
            }
            k = k->next;
        }
        return vHead.next;
    }
};
