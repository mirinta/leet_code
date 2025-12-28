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
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 *
 * 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足
 * x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 *
 * ! 所有节点的值都是唯一的。
 * ! p、q 为不同节点且均存在于给定的二叉搜索树中。
 *
 * ! 本题与LC 235相同。
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || !p || !q)
            return nullptr;

        const int min = std::min(p->val, q->val);
        const int max = std::max(p->val, q->val);
        if (min > root->val)
            return lowestCommonAncestor(root->right, p, q);

        if (max < root->val)
            return lowestCommonAncestor(root->left, p, q);

        return root;
    }
};
