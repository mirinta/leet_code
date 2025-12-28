#include <stack>

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
 * Given the head of a singly linked list, return true if it is a palindrome or false otherwise.
 *
 * ! The number of nodes in the list is in the range [1, 10^5].
 * ! 0 <= Node.val <= 9
 */

class Solution {
public:
    bool isPalindrome(ListNode* head)
    {
        if (!head)
            return false;

        if (!head->next)
            return true;

        // 1->2->2->1->NULL
        // 1->2->3->2->1->NULL
        auto* fast = head;
        auto* slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast) {
            slow = slow->next;
        }
        auto* reversedHead = reverse(slow);
        while (reversedHead) {
            if (reversedHead->val != head->val)
                return false;

            reversedHead = reversedHead->next;
            head = head->next;
        }
        return true;
    }

private:
    ListNode* reverse(ListNode* head)
    {
        ListNode* prev = nullptr;
        while (head) {
            auto* next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};