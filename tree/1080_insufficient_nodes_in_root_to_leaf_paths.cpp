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
 * Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree
 * simultaneously, and return the root of the resulting binary tree.
 *
 * A node is insufficient if every root to leaf path intersecting this node has a sum strictly less
 * than limit.
 *
 * A leaf is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [1, 5000].
 * ! -10^5 <= Node.val <= 10^5
 * ! -10^9 <= limit <= 10^9
 */

class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit)
    {
        /**
         * if X is a leaf node and the path sum from root to X is strictly less than limit,
         * X needs to be removed
         *
         * if X is not a leaf node, and assume X1 and X2 are its child nodes
         * if both of them are removed, then X needs to be removed
         * if one of them is not removed, we need to keep X
         *    X
         *   / \
         *  X1  X2
         */
        return dfs(root, 0, limit);
    }

private:
    TreeNode* dfs(TreeNode* root, int pathSum, int limit)
    {
        if (!root)
            return nullptr;

        pathSum += root->val;
        if (!root->left && !root->right)
            return pathSum < limit ? nullptr : root;

        root->left = dfs(root->left, pathSum, limit);
        root->right = dfs(root->right, pathSum, limit);
        if (!root->left && !root->right)
            return nullptr;

        return root;
    }
};
