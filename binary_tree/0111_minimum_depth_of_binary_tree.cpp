#include <queue>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given a binary tree, find its minimum depth.
 *
 * The minimum depth is the number of nodes along the shortest path from the root node down to the
 * nearest leaf node.
 *
 * Note: A leaf is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [0, 10^5].
 * ! -1000 <= Node.val <= 1000
 */

class Solution
{
public:
    int minDepth(TreeNode* root) { return approach2(root); }

private:
    // DFS, time O(N), space O(N)
    int approach2(TreeNode* root)
    {
        if (!root)
            return 0;

        if (!root->left)
            return 1 + approach2(root->right);

        if (!root->right)
            return 1 + approach2(root->left);

        return 1 + std::min(approach2(root->left), approach2(root->right));
    }

    // BFS, time O(N), space O(N)
    int approach1(TreeNode* root)
    {
        if (!root)
            return 0;

        // level-order traverse, once we reach a leaf node,
        // its depth is the final answer
        int result = 1; // we count the num of nodes along the path
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int size = queue.size(); size > 0; --size) {
                auto* node = queue.front();
                queue.pop();
                if (!node->left && !node->right)
                    return result;

                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result++;
        }
        return -1;
    }
};
