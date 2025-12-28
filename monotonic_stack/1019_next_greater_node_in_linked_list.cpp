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
 * You are given the head of a linked list with n nodes.
 *
 * For each node in the list, find the value of the next greater node. That is, for each node, find
 * the value of the first node that is next to it and has a strictly larger value than it.
 *
 * Return an integer array answer where answer[i] is the value of the next greater node of the ith
 * node (1-indexed). If the ith node does not have a next greater node, set answer[i] = 0.
 *
 * ! The number of nodes in the list is n.
 * ! 1 <= n <= 10^4
 * ! 1 <= Node.val <= 10^9
 */

class Solution {
public:
    std::vector<int> nextLargerNodes(ListNode* head)
    {
        return approach2(head);
    }

private:
    std::vector<int> approach2(ListNode* head)
    {
        if (!head)
            return {};

        using Pair = std::pair<int, int>; // <index, val>
        int i = 0;
        std::stack<Pair> stack;
        std::vector<int> result;
        while (head) {
            result.push_back(0);
            while (!stack.empty() && head->val > stack.top().second) {
                result[stack.top().first] = head->val;
                stack.pop();
            }
            stack.emplace(i++, head->val);
            head = head->next;
        }
        return result;
    }

    std::vector<int> approach1(ListNode* head)
    {
        if (!head)
            return {};

        std::vector<int> nums;
        while (head) {
            nums.push_back(head->val);
            head = head->next;
        }
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= stack.top()) {
                stack.pop();
            }
            result[i] = stack.empty() ? 0 : stack.top();
            stack.push(nums[i]);
        }
        return result;
    }
};