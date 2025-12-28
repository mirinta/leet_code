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
 * The boundary of a binary tree is the concatenation of the root, the left boundary, the leaves
 * ordered from left-to-right, and the reverse order of the right boundary.
 *
 * The left boundary is the set of nodes defined by the following:
 *
 * - The root node's left child is in the left boundary. If the root does not have a left child,
 * then the left boundary is empty.
 *
 * - If a node in the left boundary and has a left child, then the left child is in the left
 * boundary.
 *
 * - If a node is in the left boundary, has no left child, but has a right child, then the right
 * child is in the left boundary.
 *
 * - The leftmost leaf is not in the left boundary.
 *
 * The right boundary is similar to the left boundary, except it is the right side of the root's
 * right subtree. Again, the leaf is not part of the right boundary, and the right boundary is empty
 * if the root does not have a right child.
 *
 * The leaves are nodes that do not have any children. For this problem, the root is not a leaf.
 *
 * Given the root of a binary tree, return the values of its boundary.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -1000 <= Node.val <= 1000
 */

class Solution {
public:
    std::vector<int> boundaryOfBinaryTree(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result{root->val};
        // find left boundary, start from root->left
        std::vector<int> leftBoundary;
        getLeftBoundary(leftBoundary, root->left);
        for (const auto& val : leftBoundary) {
            result.push_back(val);
        }
        // if root is not a leaf node, find all leaves
        if (root->left || root->right) {
            std::vector<int> leaves;
            getLeaves(leaves, root);
            for (const auto& val : leaves) {
                result.push_back(val);
            }
        }
        // find right boundary, start from root->right
        std::vector<int> rightBoundary;
        getRightBoundary(rightBoundary, root->right);
        std::reverse(rightBoundary.begin(), rightBoundary.end());
        for (const auto& val : rightBoundary) {
            result.push_back(val);
        }
        return result;
    }

private:
    void getLeftBoundary(std::vector<int>& nums, TreeNode* root)
    {
        if (!root)
            return;

        if (root->left || root->right) {
            // exclude leaves
            nums.push_back(root->val);
        }
        if (root->left) {
            getLeftBoundary(nums, root->left);
        } else if (root->right) {
            getLeftBoundary(nums, root->right);
        }
    }

    void getRightBoundary(std::vector<int>& nums, TreeNode* root)
    {
        if (!root)
            return;

        if (root->left || root->right) {
            // exclude leaves
            nums.push_back(root->val);
        }
        if (root->right) {
            getRightBoundary(nums, root->right);
        } else if (root->left) {
            getRightBoundary(nums, root->left);
        }
    }

    void getLeaves(std::vector<int>& nums, TreeNode* root)
    {
        if (!root)
            return;

        if (!root->left && !root->right) {
            nums.push_back(root->val);
        } else {
            getLeaves(nums, root->left);
            getLeaves(nums, root->right);
        }
    }
};
