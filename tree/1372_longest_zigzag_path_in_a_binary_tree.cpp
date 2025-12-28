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
 * You are given the root of a binary tree.
 *
 * A ZigZag path for a binary tree is defined as follow:
 *
 * - Choose any node in the binary tree and a direction (right or left).
 *
 * - If the current direction is right, move to the right child of the current node; otherwise, move
 * to the left child.
 *
 * - Change the direction from right to left or from left to right.
 *
 * - Repeat the second and third steps until you can't move in the tree.
 *
 * Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
 *
 * Return the longest ZigZag path contained in that tree.
 *
 * ! The number of nodes in the tree is in the range [1, 5 * 10^4].
 * ! 1 <= Node.val <= 100
 */

class Solution {
public:
    int longestZigZag(TreeNode* root)
    {
        if (!root)
            return 0;

        int result = 0;
        dfs(result, 0, 0, root);
        return result;
    }

private:
    void dfs(int& result, int lengthFromLeft, int lengthFromRight, TreeNode* root)
    {
        if (!root)
            return;

        result = std::max({result, lengthFromLeft, lengthFromRight});
        dfs(result, 0, lengthFromLeft + 1, root->left);
        dfs(result, lengthFromRight + 1, 0, root->right);
    }
};
