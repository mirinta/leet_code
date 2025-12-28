#include <cmath>

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
 * Given the root of a complete binary tree, return the number of the nodes in the tree.
 *
 * According to Wikipedia, every level, except possibly the last, is completely filled in a complete
 * binary tree, and all nodes in the last level are as far left as possible. It can have between 1
 * and 2h nodes inclusive at the last level h.
 *
 * Design an algorithm that runs in less than O(n) time complexity.
 *
 * ! The number of nodes in the tree is in the range [0, 5 * 10^4].
 * ! 0 <= Node.val <= 5 * 10^4
 * ! The tree is guaranteed to be complete.
 */

class Solution {
public:
    int countNodes(TreeNode* root)
    {
        return approach2(root);
    }

private:
    int approach2(TreeNode* root)
    {
        if (!root)
            return 0;

        /**
         *      root
         *      /  \
         *  left    right
         *   / \     / \
         * ... ... ... ...
         *
         * if root is a complete binary tree,
         * then at least one of its subtrees (left or right) is a perfect binary tree
         */
        int leftHeight = 0;
        auto* left = root;
        while (left) {
            leftHeight++;
            left = left->left;
        }
        int rightHeight = 0;
        auto* right = root;
        while (right) {
            rightHeight++;
            right = right->right;
        }
        if (leftHeight == rightHeight)
            return std::pow(2, leftHeight) - 1;

        return 1 + approach2(root->left) + approach2(root->right);
    }

    int approach1(TreeNode* root)
    {
        if (!root)
            return 0;

        return 1 + approach1(root->left) + approach1(root->right);
    }
};
