#include <cmath>
#include <utility>

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
 * 实现一个函数，检查二叉树是否平衡。在这个问题中，平衡树的定义如下：任意一个节点，其两棵子树的高度差不超过
 * 1。
 */

class Solution {
public:
    bool isBalanced(TreeNode* root)
    {
        return dfs(root) >= 0;
    }

private:
    int dfs(TreeNode* root)
    {
        if (!root)
            return 0;

        const int left = dfs(root->left);
        const int right = dfs(root->right);
        if (left < 0 || right < 0 || std::abs(left - right) > 1)
            return -1;

        return 1 + std::max(left, right);
    }
};