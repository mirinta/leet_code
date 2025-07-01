#include <climits>
#include <tuple>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the root of a binary tree, find the largest subtree, which is also a Binary Search Tree
 * (BST), where the largest means subtree has the largest number of nodes.
 *
 * A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned
 * properties:
 *
 * - The left subtree values are less than the value of their parent (root) node's value.
 *
 * - The right subtree values are greater than the value of their parent (root) node's value.
 *
 * Note: A subtree must include all of its descendants.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -10^4 <= Node.val <= 10^4
 */

class Solution
{
public:
    int largestBSTSubtree(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return <num of nodes, max of the tree, min of the tree>
    std::tuple<int, int, int> dfs(int& result, TreeNode* node)
    {
        if (!node)
            return {0, INT_MIN, INT_MAX};

        const auto [leftCount, leftMax, leftMin] = dfs(result, node->left);
        const auto [rightCount, rightMax, rightMin] = dfs(result, node->right);
        const int count = 1 + leftCount + rightCount;
        // a valid BST:
        // min of its right subtree > root.val > max of its left subtree
        if (node->val <= leftMax || node->val >= rightMin)
            return {count, INT_MAX, INT_MIN};

        result = std::max(result, count);
        const int max = std::max({node->val, leftMax, rightMax});
        const int min = std::min({node->val, leftMin, rightMin});
        return {count, max, min};
    }
};
