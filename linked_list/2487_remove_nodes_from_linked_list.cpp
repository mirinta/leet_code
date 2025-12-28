#include <stack>
#include <vector>

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
 * You are given the head of a linked list.
 *
 * Remove every node which has a node with a greater value anywhere to the right side of it.
 *
 * Return the head of the modified linked list.
 *
 * ! The number of the nodes in the given list is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    ListNode* removeNodes(ListNode* head)
    {
        return approach2(head);
    }

private:
    ListNode* approach2(ListNode* head)
    {
        if (!head || !head->next)
            return head;

        auto* next = approach2(head->next);
        if (head->val < next->val)
            return next;

        head->next = next;
        return head;
    }

    ListNode* approach1(ListNode* head)
    {
        std::vector<int> nums;
        for (auto* node = head; node; node = node->next) {
            nums.push_back(node->val);
        }
        const auto nextGreater = getNextGreater(nums);
        ListNode vHead(-1);
        auto* node = &vHead;
        for (int i = 0; i < nums.size(); ++i) {
            if (nextGreater[i] == nums.size()) {
                node->next = new ListNode(nums[i]);
                node = node->next;
            }
        }
        return vHead.next;
    }

    std::vector<int> getNextGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};