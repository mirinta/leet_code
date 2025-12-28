/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Given the heads of two singly linked-lists "headA" and "headB", return the node at which the two
 * lists intersect. If the two linked lists have no intersection at all, return "nullptr".
 *
 * The test cases are generated such that there are no cycles anywhere in the entire linked
 * structure.
 *
 * Note that the linked lists must retain their original structure after the function returns.
 *
 * ! The number of nodes of listA is in the m.
 * ! The number of nodes of listB is in the n.
 * ! 1 <= m, n <= 3 * 10^4
 * ! 1 <= Node.val <= 10^5
 * ! 0 <= skipA < m
 * ! 0 <= skipB < n
 * ! intersectVal is 0 if listA and listB do not intersect.
 * ! intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
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