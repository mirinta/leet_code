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
 * Given the root of a binary tree, return the maximum average value of a subtree of that tree.
 * Answers within 10-5 of the actual answer will be accepted.
 *
 * A subtree of a tree is any node of that tree plus all its descendants.
 *
 * The average value of a tree is the sum of its values, divided by the number of nodes.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 0 <= Node.val <= 10^5
 */

class Solution {
public:
    double maximumAverageSubtree(TreeNode* root)
    {
        double result = 0; // 0 <= Node.val <= 10^5
        dfs(result, root);
        return result;
    }

private:
    std::pair<int, int> dfs(double& result, TreeNode* root)
    {
        if (!root)
            return {0, 0};

        const auto [leftCount, leftSum] = dfs(result, root->left);
        const auto [rightCount, rightSum] = dfs(result, root->right);
        const auto count = leftCount + rightCount + 1;
        const auto sum = leftSum + rightSum + root->val;
        result = std::max(result, sum * 1.0 / count);
        return {count, sum};
    }
};
