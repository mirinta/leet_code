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
 * You are given the root of a binary search tree (BST) and an integer val.
 *
 * Find the node in the BST that the node's value equals val and return the subtree rooted with that
 * node. If such a node does not exist, return null.
 *
 * ! The number of nodes in the tree is in the range [1, 5000].
 * ! 1 <= Node.val <= 10^7
 * ! root is a binary search tree.
 * ! 1 <= val <= 10^7
 */

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val)
    {
        return approach2(root, val);
    }

private:
    TreeNode* approach2(TreeNode* root, int val)
    {
        if (!root)
            return nullptr;

        auto* node = root;
        while (node) {
            if (node->val == val)
                return node;

            if (node->val > val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }

    TreeNode* approach1(TreeNode* root, int val)
    {
        if (!root)
            return nullptr;

        if (root->val > val)
            return searchBST(root->left, val);

        if (root->val < val)
            return searchBST(root->right, val);

        return root;
    }
};
