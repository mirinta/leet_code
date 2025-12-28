#include <queue>

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
 * A binary tree is named Even-Odd if it meets the following conditions:
 *
 * - The root of the binary tree is at level index 0, its children are at level index 1, their
 * children are at level index 2, etc.
 *
 * - For every even-indexed level, all nodes at the level have odd integer values in strictly
 * increasing order (from left to right).
 *
 * - For every odd-indexed level, all nodes at the level have even integer values in strictly
 * decreasing order (from left to right).
 *
 * Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise
 * return false.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^6
 */

class Solution {
public:
    bool isEvenOddTree(TreeNode* root)
    {
        std::queue<TreeNode*> queue;
        queue.push(root);
        bool isEven = true;
        while (!queue.empty()) {
            int prev = isEven ? INT_MIN : INT_MAX;
            for (int k = queue.size(); k > 0; --k) {
                auto* node = queue.front();
                queue.pop();
                if (isEven ? node->val % 2 == 0 : node->val % 2 != 0)
                    return false;

                if (isEven ? prev >= node->val : prev <= node->val)
                    return false;

                prev = node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            isEven = !isEven;
        }
        return true;
    }
};