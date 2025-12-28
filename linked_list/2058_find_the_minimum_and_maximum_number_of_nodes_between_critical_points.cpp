#include <climits>
#include <vector>

/**
 * Definition for singly-linked list.\
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * A critical point in a linked list is defined as either a local maxima or a local minima.
 *
 * A node is a local maxima if the current node has a value strictly greater than the previous node
 * and the next node.
 *
 * A node is a local minima if the current node has a value strictly smaller than the previous node
 * and the next node.
 *
 * Note that a node can only be a local maxima/minima if there exists both a previous node and a
 * next node.
 *
 * Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where
 * minDistance is the minimum distance between any two distinct critical points and maxDistance is
 * the maximum distance between any two distinct critical points. If there are fewer than two
 * critical points, return [-1, -1].
 *
 * ! The number of nodes in the list is in the range [2, 10^5].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head)
    {
        std::vector<int> positions;
        ListNode* prev = nullptr;
        int index = 0;
        while (head) {
            if (isCriticalPoint(head, prev)) {
                positions.push_back(index);
            }
            index++;
            prev = head;
            head = head->next;
        }
        if (positions.size() < 2)
            return {-1, -1};

        int minDist = INT_MAX;
        for (int i = 0; i + 1 < positions.size(); ++i) {
            minDist = std::min(minDist, positions[i + 1] - positions[i]);
        }
        return {minDist, positions.back() - positions.front()};
    }

private:
    bool isCriticalPoint(ListNode* node, ListNode* prev)
    {
        if (!node || !prev || !node->next)
            return false;

        if (node->val > prev->val && node->val > node->next->val)
            return true;

        if (node->val < prev->val && node->val < node->next->val)
            return true;

        return false;
    }
};
