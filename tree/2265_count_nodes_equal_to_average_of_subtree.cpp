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
        if (!root)
            return 0;

        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return[0] = num of nodes
    // return[1] = total sum of all the nodes
    std::pair<int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {0, 0};

        const auto [leftCount, leftSum] = dfs(result, root->left);
        const auto [rightCount, rightSum] = dfs(result, root->right);
        const auto sum = root->val + leftSum + rightSum;
        const auto count = leftCount + rightCount + 1;
        if (sum / count == root->val) {
            result++;
        }
        return {count, sum};
    }
};
