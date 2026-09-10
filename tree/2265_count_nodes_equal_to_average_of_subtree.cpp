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
 * Given the root of a binary tree, return the number of nodes where the value of the node is equal
 * to the average of the values in its subtree.
 *
 * Note:
 *
 * - The average of n elements is the sum of the n elements divided by n and rounded down to the
 * nearest integer.
 *
 * - A subtree of root is a tree consisting of root and all of its descendants.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! 0 <= Node.val <= 1000
 */

class Solution {
public:
    int averageOfSubtree(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return <num of nodes, sum of nodes>
    std::pair<int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {0, 0};

        const auto [lCount, lSum] = dfs(result, root->left);
        const auto [rCount, rSum] = dfs(result, root->right);
        const int count = lCount + rCount + 1;
        const int sum = lSum + rSum + root->val;
        result += sum / count == root->val;
        return {count, sum};
    }
};
