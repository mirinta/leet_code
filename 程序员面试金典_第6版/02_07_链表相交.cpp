/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 给你两个单链表的头节点 headA 和 headB
 * ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
 *
 * 题目数据 保证 整个链式结构中不存在环。
 *
 * 注意，函数返回结果后，链表必须 保持其原始结构 。
 *
 * ! listA 中节点数目为 m
 * ! listB 中节点数目为 n
 * ! 0 <= m, n <= 3 * 10^4
 * ! 1 <= Node.val <= 10^5
 * ! 0 <= skipA <= m
 * ! 0 <= skipB <= n
 * ! 如果 listA 和 listB 没有交点，intersectVal 为 0
 * ! 如果 listA 和 listB 有交点，intersectVal == listA[skipA + 1] == listB[skipB + 1]
 *
 * ! 你能否设计一个时间复杂度 O(n) 、仅用 O(1) 内存的解决方案？
 */

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        if (!headA || !headB)
            return nullptr;

        auto* a = headA;
        auto* b = headB;
        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        return a;
    }
};