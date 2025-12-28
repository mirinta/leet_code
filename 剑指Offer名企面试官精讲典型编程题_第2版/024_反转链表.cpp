/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
 *
 * ! 0 <= 节点个数 <= 5000
 *
 * ! 本题与LC 206相同。
 */

class Solution {
public:
    ListNode* reverseList(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode* prev = nullptr;
        ListNode* current = head;
        while (current) {
            auto* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }
};