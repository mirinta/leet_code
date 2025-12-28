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
 * Given the "head" of a linked list and a value "x", partition it such that all nodes less than "x"
 * come before nodes greater than or equal to "x".
 *
 * You should preserve the original relative order of the nodes in each of the two partitions.
 *
 * ! The number of nodes in the list is in the range [0, 200].
 * ! -100 <= Node.val <= 100
 * ! -200 <= x <= 200
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x)
    {
        if (!head)
            return nullptr;

        ListNode vHeadLt(-1); // less than x
        auto* lt = &vHeadLt;
        ListNode vHeadGe(-1); // greater or equal to x
        auto* ge = &vHeadGe;
        auto* current = head;
        while (current) {
            auto* next = current->next;
            current->next = nullptr;
            if (current->val < x) {
                lt->next = current;
                lt = lt->next;
            } else {
                ge->next = current;
                ge = ge->next;
            }
            current = next;
        }
        lt->next = vHeadGe.next;
        return vHeadLt.next;
    }
};
