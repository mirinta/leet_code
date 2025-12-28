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
 * 设计并实现一个算法，找出二叉树中某两个节点的第一个共同祖先。不得将其他的节点存储在另外的数据结构中。注意：这不一定是二叉搜索树。
 *
 * ! 所有节点的值都是唯一的。
 * ! p、q 为不同节点且均存在于给定的二叉树中。
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        TreeNode* result = nullptr;
        dfs(result, root, p->val, q->val);
        return result;
    }

private:
    int dfs(TreeNode*& result, TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        int count = root->val == val1 || root->val == val2;
        count += dfs(result, root->left, val1, val2);
        count += dfs(result, root->right, val1, val2);
        if (count == 2 && !result) {
            result = root;
        }
        return count;
    }
};