/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
 *
 * ! 0 <= 链表长度 <= 1000
 *
 * ! 本题与LC 21相同。
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        return approach2(l1, l2);
    }

private:
    // two pointers
    ListNode* approach2(ListNode* l1, ListNode* l2)
    {
        // two pointers
        if (!l1)
            return l2;

        if (!l2)
            return l1;

        ListNode vHead(-1);
        auto* p = &vHead;
        auto* p1 = l1;
        auto* p2 = l2;
        while (p1 || p2) {
            if (!p1) {
                p->next = p2;
                p2 = p2->next;
            } else if (!p2) {
                p->next = p1;
                p1 = p1->next;
            } else if (p1->val > p2->val) {
                p->next = p2;
                p2 = p2->next;
            } else {
                p->next = p1;
                p1 = p1->next;
            }
            p = p->next;
        }
        return vHead.next;
    }

    // recursion
    ListNode* approach1(ListNode* l1, ListNode* l2)
    {
        if (!l1)
            return l2;

        if (!l2)
            return l1;

        if (l1->val > l2->val) {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
};