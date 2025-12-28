#include <limits>
#include <tuple>

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
 * Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a
 * Binary Search Tree (BST).
 *
 * Assume a BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [1, 4 * 10^4].
 * ! -4 * 10^4 <= Node.val <= 4 * 10^4
 */

class Solution {
public:
    int maxSumBST(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // similar to LC.98, validate BST by post-order traversal
    // return <min, max, sum> of the given tree
    // if it is not a BST, return <INT_MIN, INT_MAX, 0>
    std::tuple<int, int, int> dfs(int& result, TreeNode* root)
    {
        if (!root)
            return {INT_MAX, INT_MIN, 0};

        auto [leftMin, leftMax, leftSum] = dfs(result, root->left);
        auto [rightMin, rightMax, rightSum] = dfs(result, root->right);
        // a valid BST: leftMax < root.val < rightMin
        if (leftMax >= root->val || root->val >= rightMin)
            return {INT_MIN, INT_MAX, 0};

        const int sum = leftSum + rightSum + root->val;
        result = std::max(result, sum);
        return {std::min(leftMin, root->val), std::max(rightMax, root->val), sum};
    }
};
