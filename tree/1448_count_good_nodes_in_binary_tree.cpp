
#include <limits>
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
 * Given a binary tree root, a node X in the tree is named good if in the path from root to X there
 * are no nodes with a value greater than X.
 *
 * Return the number of good nodes in the binary tree.
 *
 * ! The number of nodes in the binary tree is in the range [1, 10^5].
 * ! Each node's value is between [-10^4, 10^4].
 */

class Solution {
public:
    int goodNodes(TreeNode* root)
    {
        // assume the max value along a path from root to node X-1 is MAX,
        // we are at node X, if X.val >= MAX, then X is a good node.
        if (!root)
            return 0;

        int result = 0;
        dfs(result, INT_MIN, root);
        return result;
    }

private:
    void dfs(int& result, int prevMax, TreeNode* root)
    {
        if (!root)
            return;

        const int currMax = std::max(root->val, prevMax);
        if (currMax == root->val) {
            result++;
        }
        dfs(result, currMax, root->left);
        dfs(result, currMax, root->right);
    }
};
