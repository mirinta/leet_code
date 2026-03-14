#include <algorithm>

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
        static constexpr long long kMod = 1e9 + 7;
        long long result = 0;
        const long long total = dfs(result, 0, root);
        dfs(result, total, root);
        return result % kMod;
    }

private:
    long long dfs(long long& result, const long long total, TreeNode* node)
    {
        if (!node)
            return 0;

        const long long sum = dfs(result, total, node->left) + dfs(result, total, node->right) + node->val;
        if (total >= sum) {
            result = std::max(result, (total - sum) * sum);
        }
        return sum;
    }
};
