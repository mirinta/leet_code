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
 * Given the "root" of a binary tree and an integer targetSum, return true if the tree has a
 * root-to-leaf path such that adding up all the values along the path equals "targetSum".
 *
 * A leaf node is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [0, 5000].
 * ! -1000 <= Node.val <= 1000
 * ! -1000 <= targetSum <= 1000
 */

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum)
    {
        if (!root)
            return false;

        targetSum -= root->val;
        if (!root->left && !root->right)
            return targetSum == 0;

        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
};
