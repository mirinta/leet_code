#include <algorithm>
#include <cmath>
#include <utility>

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
 * Given a binary tree, determine if it is height-balanced.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the subtrees of every node
 * never differs by more than one.
 *
 * ! The number of nodes in the tree is in the range [0, 5000].
 * ! -10^4 <= Node.val <= 10^4
 */

class Solution {
public:
    bool isBalanced(TreeNode* root)
    {
        bool result = true;
        dfs(result, root);
        return result;
    }

private:
    int dfs(bool& result, TreeNode* node)
    {
        if (!node)
            return 0;

        const auto left = dfs(result, node->left);
        const auto right = dfs(result, node->right);
        if (std::abs(left - right) > 1) {
            result = false;
        }
        return std::max(left, right) + 1;
    }
};
