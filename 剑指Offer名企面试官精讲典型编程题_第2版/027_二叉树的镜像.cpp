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
 * 请完成一个函数，输入一个二叉树，该函数输出它的镜像。
 *
 * ! 0 <= 节点个数 <= 1000
 *
 * ! 本题与LC 226相同。
 */

class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        auto* left = mirrorTree(root->left);
        auto* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};