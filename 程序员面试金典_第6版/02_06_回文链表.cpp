/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 编写一个函数，检查输入的链表是否是回文的。
 *
 * ! 你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 */

class Solution {
public:
    bool isPalindrome(ListNode* head)
    {
        if (!head)
            return true;

        if (!head->next)
            return true;

        auto* slow = head;
        auto* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if (fast) {
            slow = slow->next; // length is odd
        }
        auto* reversed = reverse(slow);
        while (reversed) {
            if (head->val != reversed->val)
                return false;

            head = head->next;
            reversed = reversed->next;
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