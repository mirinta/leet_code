#include <vector>

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
 * Given the root of a binary tree, collect a tree's nodes as if you were doing this:
 *
 * - Collect all the leaf nodes.
 *
 * - Remove all the leaf nodes.
 *
 * - Repeat until the tree is empty.
 *
 * ! The number of nodes in the tree is in the range [1, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> findLeaves(TreeNode* root)
    {
        std::vector<std::vector<int>> result;
        while (root) {
            std::vector<int> leaves;
            root = dfs(leaves, root);
            result.push_back(leaves);
        }
        return result;
    }

private:
    // reconstruct the given tree by removing its leaf nodes
    TreeNode* dfs(std::vector<int>& leaves, TreeNode* root)
    {
        if (!root)
            return nullptr;

        if (!root->left && !root->right) {
            leaves.push_back(root->val);
            return nullptr;
        }
        root->left = dfs(leaves, root->left);
        root->right = dfs(leaves, root->right);
        return root;
    }
};
