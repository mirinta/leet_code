#include <numeric>

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
 * Given the head of a linked list head, in which each node contains an integer value.
 *
 * Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common
 * divisor of them.
 *
 * Return the linked list after insertion.
 *
 * The greatest common divisor of two numbers is the largest positive integer that evenly divides
 * both numbers.
 *
 * ! The number of nodes in the list is in the range [1, 5000].
 * ! 1 <= Node.val <= 1000
 */

class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head)
    {
        auto* node = head;
        while (node && node->next) {
            auto* next = node->next;
            node->next = new ListNode(std::gcd(node->val, next->val));
            node->next->next = next;
            node = next;
        }
        return head;
    }
};