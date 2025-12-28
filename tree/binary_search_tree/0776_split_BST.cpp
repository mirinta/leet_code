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
 * Given the root of a binary search tree (BST) and an integer target, split the tree into two
 * subtrees where the first subtree has nodes that are all smaller or equal to the target value,
 * while the second subtree has all nodes that are greater than the target value. It is not
 * necessarily the case that the tree contains a node with the value target.
 *
 * Additionally, most of the structure of the original tree should remain. Formally, for any child c
 * with parent p in the original tree, if they are both in the same subtree after the split, then
 * node c should still have the parent p.
 *
 * Return an array of the two roots of the two subtrees in order.
 *
 * ! The number of nodes in the tree is in the range [1, 50].
 * ! 0 <= Node.val, target <= 1000
 */

class Solution {
public:
    std::vector<TreeNode*> splitBST(TreeNode* root, int target)
    {
        if (!root)
            return {nullptr, nullptr};

        if (root->val > target) {
            auto split = splitBST(root->left, target);
            root->left = split[1];
            return {split[0], root};
        }
        auto split = splitBST(root->right, target);
        root->right = split[0];
        return {root, split[1]};
    }
};