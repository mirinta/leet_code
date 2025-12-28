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
 * Given the root of a binary tree, split the binary tree into two subtrees by removing one edge
 * such that the product of the sums of the subtrees is maximized.
 *
 * Return the maximum product of the sums of the two subtrees. Since the answer may be too large,
 * return it modulo 10^9 + 7.
 *
 * Note that you need to maximize the answer before taking the mod and not after taking it.
 *
 * ! The number of nodes in the tree is in the range [2, 5 * 10^4].
 * ! 1 <= Node.val <= 10^4
 */

class Solution {
public:
    int maxProduct(TreeNode* root)
    {
        constexpr int kMod = 1e9 + 7;
        const long long total = getTotalSum(root);
        long long result = 0;
        dfs(result, root, total);
        return result % kMod;
    }

private:
    long long getTotalSum(TreeNode* root)
    {
        if (!root)
            return 0;

        return root->val + getTotalSum(root->left) + getTotalSum(root->right);
    }

    long long dfs(long long& result, TreeNode* root, long long total)
    {
        if (!root)
            return 0;

        const long long left = dfs(result, root->left, total);
        const long long right = dfs(result, root->right, total);
        const long long sum = left + right + root->val;
        result = std::max(result, sum * (total - sum)); // cut this subtree
        return sum;
    }
};