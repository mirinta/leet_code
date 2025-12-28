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
 * You are given the root of a binary tree where each node has a value in the range [0, 25]
 * representing the letters 'a' to 'z'.
 *
 * Return the lexicographically smallest string that starts at a leaf of this tree and ends at the
 * root.
 *
 * As a reminder, any shorter prefix of a string is lexicographically smaller.
 *
 * For example, "ab" is lexicographically smaller than "aba".
 * A leaf of a node is a node that has no children.
 *
 * ! The number of nodes in the tree is in the range [1, 8500].
 * ! 0 <= Node.val <= 25
 */

class Solution {
public:
    std::string smallestFromLeaf(TreeNode* root)
    {
        std::string result;
        std::string path;
        dfs(result, path, root);
        return result;
    }

private:
    void dfs(std::string& result, std::string& path, TreeNode* root)
    {
        if (!root)
            return;

        path.push_back(root->val + 'a');
        if (!root->left && !root->right) {
            std::string s(path.rbegin(), path.rend());
            result = result.empty() ? s : std::min(result, s);
        }
        dfs(result, path, root->left);
        dfs(result, path, root->right);
        path.pop_back();
    }
};