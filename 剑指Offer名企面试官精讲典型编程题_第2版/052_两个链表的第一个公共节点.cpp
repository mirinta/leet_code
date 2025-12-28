
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 输入两个链表，找出它们的第一个公共节点。
 *
 * ! 如果两个链表没有交点，返回 null.
 * ! 在返回结果后，两个链表仍须保持原有的结构。
 * ! 可假定整个链表结构中没有循环。
 * ! 程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。
 *
 * ! 本题与LC 160相同。
 */

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        if (!headA || !headB)
            return nullptr;

        auto* iterA = headA;
        auto* iterB = headB;
        while (iterA != iterB) {
            iterA = iterA ? iterA->next : headB;
            iterB = iterB ? iterB->next : headA;
        }
        return iterA;
    }
};