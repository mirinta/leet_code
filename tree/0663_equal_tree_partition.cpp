#include <vector>

/**
 * Given the root of a binary tree, return true if you can partition the tree into two trees with
 * equal sums of values after removing exactly one edge on the original tree.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 */

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    bool checkEqualTree(TreeNode* root)
    {
        std::vector<int> sums;
        dfs(sums, root);
        if (sums.back() % 2)
            return false;

        for (int i = 0; i < sums.size() - 1; ++i) {
            if (sums.back() == sums[i] * 2)
                return true;
        }
        return false;
    }

private:
    int dfs(std::vector<int>& sums, TreeNode* node)
    {
        if (!node)
            return 0;

        const int sum = node->val + dfs(sums, node->left) + dfs(sums, node->right);
        sums.push_back(sum);
        return sum;
    }
};