#include <cmath>
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
 * Given the root of a binary tree, find the maximum value v for which there exist different nodes a
 * and b where v = |a.val - b.val| and a is an ancestor of b.
 *
 * A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an
 * ancestor of b.
 *
 * ! The number of nodes in the tree is in the range [2, 5000].
 * ! 0 <= Node.val <= 10^5
 */

class Solution {
public:
    int maxAncestorDiff(TreeNode* root)
    {
        int result = INT_MIN;
        dfs(result, root);
        return result;
    }

private:
    // find <min, max> value of the given tree
    std::pair<int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {INT_MAX, INT_MIN};

        if (!root->left && !root->right)
            return {root->val, root->val};

        const auto [leftMin, leftMax] = dfs(result, root->left);
        const auto [rightMin, rightMax] = dfs(result, root->right);
        const int min = std::min(leftMin, rightMin);
        const int max = std::max(leftMax, rightMax);
        result = std::max({result, std::abs(root->val - min), std::abs(root->val - max)});
        return {std::min(root->val, min), std::max(root->val, max)};
    }
};
