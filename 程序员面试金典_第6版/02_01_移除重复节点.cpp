#include <unordered_set>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。
 *
 * ! 链表长度在[0, 20000]范围内。
 * ! 链表元素在[0, 20000]范围内。
 */

class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head)
    {
        if (!head)
            return nullptr;

        std::unordered_set<int> set;
        ListNode vHead(-1);
        auto* node = &vHead;
        while (head) {
            auto* next = head->next;
            if (set.insert(head->val).second) {
                head->next = nullptr;
                node->next = head;
                node = node->next;
            }
            head = next;
        }
        return vHead.next;
    }
};