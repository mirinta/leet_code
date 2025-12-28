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
 * You are given the root of a binary tree with n nodes where each node in the tree has node.val
 * coins. There are n coins in total throughout the whole tree.
 *
 * In one move, we may choose two adjacent nodes and move one coin from one node to another. A move
 * may be from parent to child, or from child to parent.
 *
 * Return the minimum number of moves required to make every node have exactly one coin.
 *
 * ! The number of nodes in the tree is n.
 * ! 1 <= n <= 100
 * ! 0 <= Node.val <= n
 * ! The sum of all Node.val is n.
 */

class Solution {
public:
    int distributeCoins(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return = {num of nodes, num of coins}
    std::pair<int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {0, 0};

        const auto [leftNodes, leftCoins] = dfs(result, root->left);
        const auto [rightNodes, rightCoins] = dfs(result, root->right);
        const int nodes = leftNodes + rightNodes + 1;
        const int coins = root->val + leftCoins + rightCoins;
        result += std::abs(nodes - coins);
        return {nodes, coins};
    }
};