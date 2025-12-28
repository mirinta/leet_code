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
 * 设计一个算法，找出二叉搜索树中指定节点的“下一个”节点（也即中序后继）。
 *
 * 如果指定节点没有对应的“下一个”节点，则返回null。
 */

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
    {
        if (!root || !p)
            return nullptr;

        if (root->val <= p->val)
            return inorderSuccessor(root->right, p);

        auto* result = inorderSuccessor(root->left, p);
        return result ? result : root;
    }
};