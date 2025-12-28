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
 * 输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。
 *
 * ! 节点总数 <= 10000
 *
 * ! 本题与LC 104相同。
 */

class Solution {
public:
    int maxDepth(TreeNode* root)
    {
        if (!root)
            return 0;

        return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
    }
};