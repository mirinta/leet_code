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
 * Given an integer n, return a list of all possible full binary trees with n nodes. Each node of
 * each tree in the answer must have Node.val == 0.
 *
 * Each element of the answer is the root node of one possible tree. You may return the final list
 * of trees in any order.
 *
 * A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 *
 * ! 1 <= n <= 20
 */

class Solution {
public:
    std::vector<TreeNode*> allPossibleFBT(int n)
    {
        std::vector<std::vector<TreeNode*>> memo(n + 1);
        return dfs(memo, n);
    }

private:
    std::vector<TreeNode*> dfs(std::vector<std::vector<TreeNode*>>& memo, int n)
    {
        if (n == 1)
            return {new TreeNode(0)};

        if (!memo[n].empty())
            return memo[n];

        for (int left = 1; left <= n - 1; left += 2) {
            auto leftSubtrees = dfs(memo, left);
            auto rightSubtrees = dfs(memo, n - 1 - left);
            for (auto* const x : leftSubtrees) {
                for (auto* const y : rightSubtrees) {
                    auto* root = new TreeNode(0);
                    root->left = x;
                    root->right = y;
                    memo[n].push_back(root);
                }
            }
        }
        return memo[n];
    }
};