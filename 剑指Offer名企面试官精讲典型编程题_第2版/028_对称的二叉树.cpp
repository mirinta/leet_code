/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
 *
 * ! 0 <= 节点个数 <= 1000
 *
 * ! 本题与LC 101相同。
 */

class Solution {
public:
    bool isSymmetric(TreeNode* root)
    {
        if (!root)
            return true;

        return compare(root->left, root->right);
    }

private:
    bool compare(TreeNode* rootA, TreeNode* rootB)
    {
        if (!rootA && !rootB)
            return true;

        if (!rootA || !rootB)
            return false;

        if (rootA->val != rootB->val)
            return false;

        return compare(rootA->left, rootB->right) && compare(rootA->right, rootB->left);
    }
};