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
 * In a linked list of size "n", where "n" is even, the "i"th node (0-indexed) of the linked list is
 * known as the twin of the "(n-1-i)"th node, if 0 <= i <= (n / 2) - 1.
 *
 * - For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2.
 * There are the only nodes with twins for n = 4.
 *
 * The twin sum is defined as the sum of a node and its twn.
 *
 * Given the "head" of a linked list with even length, return the maximum twn sum of the linked
 * list.
 *
 * ! The number of nodes in the list is an even integer in the range [2, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    int pairSum(ListNode* head)
    {
        std::vector<int> v;
        for (auto* p = head; p; p = p->next) {
            v.push_back(p->val);
        }
        int result = INT_MIN;
        for (int i = 0, j = v.size() - 1; i < j; ++i, --j) {
            result = std::max(result, v[i] + v[j]);
        }
        return result;
    }
};
