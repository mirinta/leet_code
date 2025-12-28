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
 * Given the roots of two binary trees "p" and "q", write a function to check if they are the same
 * or not.
 *
 * Two binary trees are considered the same if they are structurally identical, and the nodes have
 * the same value.
 *
 * ! The number of nodes in both trees is in the range [0, 100].
 * ! -10^4 <= Node.val <= 10^4
 */

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if (!p && !q)
            return true;

        if (!p || !q)
            return false;

        if (p->val != q->val)
            return false;

        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};