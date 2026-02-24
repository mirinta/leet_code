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
 * You are given the root of a binary tree where each node has a value 0 or 1. Each root-to-leaf path represents a
 * binary number starting with the most significant bit.
 *
 * - For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
 *
 * For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum
 * of these numbers.
 *
 * The test cases are generated so that the answer fits in a 32-bits integer.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! Node.val is 0 or 1.
 */

class Solution {
public:
    int sumRootToLeaf(TreeNode* root)
    {
        int result = 0;
        dfs(result, root, 0);
        return result;
    }

private:
    void dfs(int& result, TreeNode* node, int n)
    {
        if (!node)
            return;

        n = 2 * n + node->val;
        if (!node->left && !node->right) {
            result += n;
        }
        dfs(result, node->left, n);
        dfs(result, node->right, n);
    }
};
