#include <string>

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
 * You are given the head of a linked list of even length containing integers.
 *
 * Each odd-indexed node contains an odd integer and each even-indexed node contains an even
 * integer.
 *
 * We call each even-indexed node and its next node a pair, e.g., the nodes with indices 0 and 1 are
 * a pair, the nodes with indices 2 and 3 are a pair, and so on.
 *
 * For every pair, we compare the values of the nodes in the pair:
 *
 * - If the odd-indexed node is higher, the "Odd" team gets a point.
 *
 * - If the even-indexed node is higher, the "Even" team gets a point.
 *
 * Return the name of the team with the higher points, if the points are equal, return "Tie".
 *
 * ! The number of nodes in the list is in the range [2, 100].
 * ! The number of nodes in the list is even.
 * ! 1 <= Node.val <= 100
 * ! The value of each odd-indexed node is odd.
 * ! The value of each even-indexed node is even.
 */

class Solution {
public:
    std::string gameResult(ListNode* head)
    {
        return approach2(head);
    }

private:
    std::string approach2(ListNode* head)
    {
        int even = 0;
        int odd = 0;
        for (auto iter = head; iter && iter->next; iter = iter->next->next) {
            if (iter->val > iter->next->val) {
                even++;
            } else if (iter->val < iter->next->val) {
                odd++;
            }
        }
        if (even == odd)
            return "Tie";

        return even > odd ? "Even" : "Odd";
    }

    std::string approach1(ListNode* head)
    {
        const auto [even, odd] = dfs(head);
        if (even == odd)
            return "Tie";

        return even > odd ? "Even" : "Odd";
    }

    std::pair<int, int> dfs(ListNode* head)
    {
        if (!head || !head->next)
            return {0, 0};

        auto [even, odd] = dfs(head->next->next);
        if (head->val > head->next->val) {
            even++;
        } else if (head->val < head->next->val) {
            odd++;
        }
        return {even, odd};
    }
};