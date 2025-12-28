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
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of
 * the original BST is changed to the original key plus the sum of all keys greater than the
 * original key in BST.
 *
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -10^4 <= Node.val <= 10^4
 * ! All the values in the tree are unique.
 * ! root is guaranteed to be a valid binary search tree.
 *
 * ! This question is the same as LC.1038.
 */

class Solution {
public:
    TreeNode* convertBST(TreeNode* root)
    {
        // traverse the BST in decreasing order
        // and record the prefix sum
        int sum = 0;
        return dfs(sum, root);
    }

private:
    TreeNode* dfs(int& sum, TreeNode* root)
    {
        if (!root)
            return nullptr;

        dfs(sum, root->right);
        sum += root->val;
        root->val = sum;
        dfs(sum, root->left);
        return root;
    }
};