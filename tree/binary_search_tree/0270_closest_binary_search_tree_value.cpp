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
 * Given the root of a binary search tree and a target value, return the value in the BST that is
 * closest to the target. If there are multiple answers, print the smallest.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 0 <= Node.val <= 10^9
 * ! -10^9 <= target <= 10^9
 */

class Solution {
public:
    int closestValue(TreeNode* root, double target)
    {
        if (!root)
            return -1;

        int result = root->val;
        while (root) {
            const auto diff1 = std::abs(result - target);
            const auto diff2 = std::abs(root->val - target);
            if (diff1 > diff2 || (diff1 == diff2 && root->val < result)) {
                result = root->val;
            }
            root = target < root->val ? root->left : root->right;
        }
        return result;
    }
};
