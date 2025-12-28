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
 * Given a binary tree root and an integer target, delete all the leaf nodes with value target.
 *
 * Note that once you delete a leaf node with value target, if its parent node becomes a leaf node
 * and has the value target, it should also be deleted (you need to continue doing that until you
 * cannot).
 *
 * ! The number of nodes in the tree is in the range [1, 3000].
 * ! 1 <= Node.val, target <= 1000
 */

class Solution {
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target)
    {
        if (!root)
            return nullptr;

        if (!root->left && !root->right)
            return root->val == target ? nullptr : root;

        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        if (!root->left && !root->right && root->val == target)
            return nullptr;

        return root;
    }
};