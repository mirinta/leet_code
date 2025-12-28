#include <limits>
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
 * Given the root of a binary tree, return the length of the longest consecutive sequence path.
 *
 * A consecutive sequence path is a path where the values increase by one along the path.
 *
 * Note that the path can start at any node in the tree, and you cannot go from a node to its parent
 * in the path.
 *
 * ! The number of nodes in the tree is in the range [1, 3 * 10^4].
 * ! -3 * 10^4 <= Node.val <= 3 * 10^4
 */

class Solution {
public:
    int longestConsecutive(TreeNode* root)
    {
        return approach1(root);
    }

private:
    // preorder-traversal
    int approach1(TreeNode* root)
    {
        int result = 0;
        preorder(result, 0, INT_MIN, root);
        return result;
    }

    void preorder(int& result, int count, int prev, TreeNode* root)
    {
        if (!root)
            return;

        const auto expected = prev + 1;
        count = root->val == expected ? count + 1 : 1;
        result = std::max(result, count);
        preorder(result, count, root->val, root->left);
        preorder(result, count, root->val, root->right);
    }

    // post-order traversal
    int approach2(TreeNode* root)
    {
        int result = 0;
        postorder(result, root);
        return result;
    }

    int postorder(int& result, TreeNode* root)
    {
        if (!root)
            return 0;

        auto left = postorder(result, root->left);
        auto right = postorder(result, root->right);
        if (root->left && root->left->val == root->val + 1) {
            left++;
        } else {
            left = 1;
        }
        if (root->right && root->right->val == root->val + 1) {
            right++;
        } else {
            right = 1;
        }
        result = std::max({result, left, right});
        return std::max(left, right);
    }
};
