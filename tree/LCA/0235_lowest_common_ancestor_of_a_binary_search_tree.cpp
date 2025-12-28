#include <algorithm>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes
 * in the BST.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between
 * two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a
 * node to be a descendant of itself).”
 *
 * ! The number of nodes in the tree is in the range [2, 10^5].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 * ! p and q will exist in the BST.
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        // p and q are guaranteed in the tree
        // and all node.val are unique
        if (!root)
            return nullptr;

        // case 1: both p and q are in the left subtree of root
        if (std::max(p->val, q->val) < root->val)
            return lowestCommonAncestor(root->left, p, q);

        // case 2: both p and q are in the right subtree of root
        if (std::min(p->val, q->val) > root->val)
            return lowestCommonAncestor(root->right, p, q);

        // case3: p and q are in the different subtrees of root
        return root;
    }
};
