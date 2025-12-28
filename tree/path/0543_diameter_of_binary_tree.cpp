#include <utility>

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
 * Given the "root" of a binary tree, return the length of the diameter of the tree.
 *
 * The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
 * This path may or may not pass through the "root".
 *
 * The length of a path between two nodes is represented by the number of edges between them.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    int dfs(int& result, TreeNode* root)
    {
        if (!root)
            return 0;

        const int leftMaxDepth = dfs(result, root->left);
        const int rightMaxDepth = dfs(result, root->right);
        result = std::max(result, leftMaxDepth + rightMaxDepth);
        return 1 + std::max(leftMaxDepth, rightMaxDepth);
    }
};
