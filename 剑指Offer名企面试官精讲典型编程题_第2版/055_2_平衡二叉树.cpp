#include <cmath>
#include <utility>

/**
 *  Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
 *
 * ! 0 <= 树的结点个数 <= 10000
 *
 * ! 本题与LC 110相同。
 */

class Solution {
public:
    bool isBalanced(TreeNode* root)
    {
        if (!root)
            return true;

        bool isBalance = true;
        height(isBalance, root);
        return isBalance;
    }

private:
    int height(bool& isBalance, TreeNode* root)
    {
        if (!root)
            return 0;

        const int left = height(isBalance, root->left);
        const int right = height(isBalance, root->right);
        if (std::abs(left - right) > 1) {
            isBalance = false;
        }
        return 1 + std::max(left, right);
    }
};