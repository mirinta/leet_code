#include <string>

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

/**
 * Given the root of a binary tree, construct a string consisting of parenthesis and integers from a
 * binary tree with the preorder traversal way, and return it.
 *
 * Omit all the empty parenthesis pairs that do not affect the one-to-one mapping relationship
 * between the string and the original binary tree.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -1000 <= Node.val <= 1000
 */

class Solution {
public:
    std::string tree2str(TreeNode* root)
    {
        if (!root)
            return {};

        std::string result;
        dfs(result, root);
        return result;
    }

private:
    void dfs(std::string& result, TreeNode* root)
    {
        if (!root)
            return;

        result.append(std::to_string(root->val));
        if (!root->left && !root->right)
            return;

        result.push_back('(');
        dfs(result, root->left);
        result.push_back(')');
        if (root->right) {
            result.push_back('(');
            dfs(result, root->right);
            result.push_back(')');
        }
    }
};