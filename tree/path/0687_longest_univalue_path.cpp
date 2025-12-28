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
 * Given the root of a binary tree, return the length of the longest path, where each node in the
 * path has the same value. This path may or may not pass through the root.
 *
 * The length of the path between two nodes is represented by the number of edges between them.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -1000 <= Node.val <= 1000
 * ! The depth of the tree will not exceed 1000.
 */

class Solution {
public:
    int longestUnivaluePath(TreeNode* root)
    {
        // #NOTE# length of a path = number of edges = number of nodes - 1
        // Here, we define the length of a path = the number of nodes along the path.
        int result = 0;
        dfs(result, root);
        return result == 0 ? result : result - 1;
    }

private:
    int dfs(int& result, TreeNode* root)
    {
        if (!root)
            return 0;

        int left = dfs(result, root->left);
        int right = dfs(result, root->right);
        if (root->left && root->val != root->left->val) {
            left = 0;
        }
        if (root->right && root->val != root->right->val) {
            right = 0;
        }
        result = std::max(result, 1 + left + right); // +1 to include the root
        return 1 + std::max(left, right);            // +1 to include the root
    }
};