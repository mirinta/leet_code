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
 * Given the root of a binary tree, return the length of the longest consecutive path in the tree.
 *
 * A consecutive path is a path where the values of the consecutive nodes in the path differ by one.
 * This path can be either increasing or decreasing.
 *
 * - For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not
 * valid.
 *
 * On the other hand, the path can be in the child-Parent-child order, where not necessarily be
 * parent-child order.
 *
 * ! The number of nodes in the tree is in the range [1, 3 * 10^4].
 * ! -3 * 10^4 <= Node.val <= 3 * 10^4
 */

class Solution {
public:
    int longestConsecutive(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return[0] = length of the longest consecutive [decreasing] path
    // return[1] = length of the longest consecutive [increasing] path
    // length of a path = num of nodes along the path
    std::pair<int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {0, 0};

        auto [leftDecrease, leftIncrease] = dfs(result, root->left);
        auto [rightDecrease, rightIncrease] = dfs(result, root->right);
        if (root->left && root->left->val + 1 == root->val) {
            leftDecrease++;
            leftIncrease = 1;
        } else if (root->left && root->left->val - 1 == root->val) {
            leftIncrease++;
            leftDecrease = 1;
        } else {
            leftIncrease = 1;
            leftDecrease = 1;
        }
        if (root->right && root->right->val + 1 == root->val) {
            rightDecrease++;
            rightIncrease = 1;
        } else if (root->right && root->right->val - 1 == root->val) {
            rightIncrease++;
            rightDecrease = 1;
        } else {
            rightIncrease = 1;
            rightDecrease = 1;
        }
        result = std::max({result, leftIncrease + rightDecrease - 1, leftDecrease + rightIncrease - 1});
        return {std::max(leftDecrease, rightDecrease), std::max(leftIncrease, rightIncrease)};
    }
};
