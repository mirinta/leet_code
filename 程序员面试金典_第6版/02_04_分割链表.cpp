/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在
 * 大于或等于 x 的节点之前。
 *
 * 你不需要 保留 每个分区中各节点的初始相对位置。
 *
 * ! 链表中节点的数目在范围 [0, 200] 内
 * ! -100 <= Node.val <= 100
 * ! -200 <= x <= 200
 */

class Solution {
public:
    ListNode* partition(ListNode* head, int x)
    {
        if (!head)
            return nullptr;

        ListNode vHead1(-1);
        ListNode vHead2(-1);
        auto* iter1 = &vHead1;
        auto* iter2 = &vHead2;
        while (head) {
            if (head->val < x) {
                iter1->next = head;
                iter1 = iter1->next;
            } else {
                iter2->next = head;
                iter2 = iter2->next;
            }
            head = head->next;
        }
        iter2->next = nullptr;
        iter1->next = vHead2.next;
        return vHead1.next;
    }
};