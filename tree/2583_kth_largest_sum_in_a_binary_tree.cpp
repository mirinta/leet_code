#include <queue>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * You are given the root of a binary tree and a positive integer k.
 *
 * The level sum in the tree is the sum of the values of the nodes that are on the same level.
 *
 * Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than
 * k levels in the tree, return -1.
 *
 * Note that two nodes are on the same level if they have the same distance from the root.
 *
 * ! The number of nodes in the tree is n.
 * ! 2 <= n <= 10^5
 * ! 1 <= Node.val <= 10^6
 * ! 1 <= k <= n
 */

class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k)
    {
        std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            long long sum = 0;
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                sum += node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            pq.push(sum);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.size() == k ? pq.top() : -1;
    }
};