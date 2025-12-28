#include <stack>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
 */

class Solution {
public:
    std::vector<int> reversePrint(ListNode* head)
    {
        return approach3(head);
    }

private:
    std::vector<int> approach1(ListNode* head)
    {
        if (!head)
            return {};

        std::stack<int> stack;
        for (auto* p = head; p; p = p->next) {
            stack.push(p->val);
        }
        std::vector<int> result;
        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
        return result;
    }

    std::vector<int> approach2(ListNode* head)
    {
        std::vector<int> result;
        traverse(result, head);
        return result;
    }

    void traverse(std::vector<int>& result, ListNode* node)
    {
        if (!node)
            return;

        traverse(result, node->next);
        result.push_back(node->val);
    }

    std::vector<int> approach3(ListNode* head)
    {
        if (!head)
            return {};

        std::vector<int> result;
        auto* reversedHead = reverseLinkedList(head);
        for (auto* p = reversedHead; p; p = p->next) {
            result.push_back(p->val);
        }
        reverseLinkedList(reversedHead); // restore
        return result;
    }

    ListNode* reverseLinkedList(ListNode* head)
    {
        if (!head)
            return nullptr;

        //       1->2->3
        //    ^  ^
        // prev  current
        auto* current = head;
        ListNode* prev = nullptr;
        while (current) {
            auto* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } // the loop is terminated when current == nullptr
        return prev;
    }
};