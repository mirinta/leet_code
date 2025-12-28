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

class Solution {
public:
    int countUnivalSubtrees(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return true is all values in the given tree are the same
    bool dfs(int& result, TreeNode* root)
    {
        if (!root)
            return true;

        const auto leftAllSame = dfs(result, root->left);
        const auto rightAllSame = dfs(result, root->right);
        if (!leftAllSame || !rightAllSame)
            return false;

        // both subtrees are empty
        const auto case1 = !root->left && !root->right;
        // left subtree is emtpy, right subtree is the same as the root
        const auto case2 = !root->left && (root->right && root->right->val == root->val);
        // left subtree is the same as the root, right subtree is empty
        const auto case3 = (root->left && root->left->val == root->val) && !root->right;
        // both subtrees are the same as the root
        const auto case4 =
            (root->left && root->left->val == root->val) && (root->right && root->right->val == root->val);
        if (case1 || case2 || case3 || case4) {
            result++;
            return true;
        }
        return false;
    }
};
