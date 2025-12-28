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
 * You are given the head of a linked list, which contains a series of integers separated by 0's.
 * The beginning and end of the linked list will have Node.val == 0.
 *
 * For every two consecutive 0's, merge all the nodes lying in between them into a single node whose
 * value is the sum of all the merged nodes. The modified list should not contain any 0's.
 *
 * Return the head of the modified linked list.
 *
 * ! The number of nodes in the list is in the range [3, 2 * 105].
 * ! 0 <= Node.val <= 1000
 * ! There are no two consecutive nodes with Node.val == 0.
 * ! The beginning and end of the linked list have Node.val == 0.
 */

class Solution {
public:
    ListNode* mergeNodes(ListNode* head)
    {
        ListNode vHead(-1);
        auto* curr = &vHead;
        while (head) {
            while (head && head->val == 0) {
                head = head->next;
            }
            int sum = 0;
            while (head && head->val != 0) {
                sum += head->val;
                head = head->next;
            }
            if (sum != 0) {
                curr->next = new ListNode(sum);
                curr = curr->next;
            }
        }
        return vHead.next;
    }
};