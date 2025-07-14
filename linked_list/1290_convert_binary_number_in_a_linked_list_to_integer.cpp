/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Given head which is a reference node to a singly-linked list. The value of each node in the
 * linked list is either 0 or 1. The linked list holds the binary representation of a number.
 *
 * Return the decimal value of the number in the linked list.
 *
 * The most significant bit is at the head of the linked list.
 *
 * ! The Linked List is not empty.
 * ! Number of nodes will not exceed 30.
 * ! Each node's value is either 0 or 1.
 */

class Solution
{
public:
    int getDecimalValue(ListNode* head)
    {
        int result = 0;
        while (head) {
            result = (result << 1) + head->val;
            head = head->next;
        }
        return result;
    }
};
