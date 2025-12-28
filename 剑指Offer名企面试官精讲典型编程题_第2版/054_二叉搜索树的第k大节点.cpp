#include <vector>

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
 * 给定一棵二叉搜索树，请找出其中第 k 大的节点的值。
 *
 * ! 1 ≤ k ≤ 二叉搜索树元素个数
 */

class Solution {
public:
    int kthLargest(TreeNode* root, int k)
    {
        std::vector<int> inorder;
        traverse(inorder, root);
        return inorder[inorder.size() - k];
    }

private:
    void traverse(std::vector<int>& inorder, TreeNode* node)
    {
        if (!node)
            return;

        traverse(inorder, node->left);
        inorder.push_back(node->val);
        traverse(inorder, node->right);
    }
};