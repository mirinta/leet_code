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
 * Given the "head" of a linked list and an integer "val", remove all the nodes of the linked list
 * that has "Node.val == val", and return the new head.
 *
 * ! The number of nodes in the list is in the range [0, 104].
 * ! 1 <= Node.val <= 50
 * ! 0 <= val <= 50
 */

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        return approach2(head, val);
    }

private:
    ListNode* approach2(ListNode* head, int val)
    {
        ListNode vHead(-1);
        auto* node = &vHead;
        for (auto* i = head; i; i = i->next) {
            if (i->val != val) {
                node->next = i;
                node = node->next;
            }
        }
        node->next = nullptr;
        return vHead.next;
    }

    ListNode* approach1(ListNode* head, int val)
    {
        while (head && head->val == val) {
            head = head->next;
        }
        auto* node = head;
        while (node) {
            auto* next = node->next;
            while (next && next->val == val) {
                next = next->next;
            }
            node->next = next;
            node = node->next;
        }
        return head;
    }
};