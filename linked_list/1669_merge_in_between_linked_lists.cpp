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
 * You are given two linked lists: list1 and list2 of sizes n and m respectively.
 *
 * Remove list1's nodes from the ath node to the bth node, and put list2 in their place.
 *
 * Build the result list and return its head.
 *
 * ! 3 <= list1.length <= 10^4
 * ! 1 <= a <= b < list1.length - 1
 * ! 1 <= list2.length <= 10^4
 */

class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2)
    {
        ListNode vHead(-1);
        vHead.next = list1;
        auto* prevA = getNthNode(&vHead, a);
        auto* B = getNthNode(&vHead, b + 1);
        auto* tail2 = list2;
        while (tail2 && tail2->next) {
            tail2 = tail2->next;
        }
        prevA->next = list2;
        tail2->next = B->next;
        B->next = nullptr;
        return vHead.next;
    }

private:
    ListNode* getNthNode(ListNode* head, int n)
    {
        auto* node = head;
        for (int i = 0; i < n; ++i) {
            node = node->next;
        }
        return node;
    }
};