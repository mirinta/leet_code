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
 * You are given the head of a linked list and two integers m and n.
 *
 * Traverse the linked list and remove some nodes in the following way:
 *
 * - Start with the head as the current node.
 *
 * - Keep the first m nodes starting with the current node.
 *
 * - Remove the next n nodes
 *
 * - Keep repeating steps 2 and 3 until you reach the end of the list.
 *
 * Return the head of the modified list after removing the mentioned nodes.
 *
 * ! The number of nodes in the list is in the range [1, 10^4].
 * ! 1 <= Node.val <= 10^6
 * ! 1 <= m, n <= 1000
 */

class Solution {
public:
    ListNode* deleteNodes(ListNode* head, int m, int n)
    {
        // 0->...->M-1->M->...->M+N-1->M+N->...
        //              |<--remove->|
        auto* prev = head;
        while (prev) {
            for (int i = 0; i < m - 1 && prev; ++i) {
                prev = prev->next;
            }
            if (!prev)
                break;

            auto* next = prev->next;
            for (int i = 0; i < n && next; ++i) {
                next = next->next;
            }
            prev->next = next;
            prev = next;
        }
        return head;
    }
};
