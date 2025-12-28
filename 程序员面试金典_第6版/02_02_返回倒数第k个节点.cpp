/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。
 *
 * ! 注意：本题相对原题稍作改动
 * ! 给定的 k 保证是有效的。
 */

class Solution {
public:
    int kthToLast(ListNode* head, int k)
    {
        auto* fast = head;
        for (int i = 0; i < k; ++i) {
            fast = fast->next;
        }
        auto* slow = head;
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow->val;
    }
};