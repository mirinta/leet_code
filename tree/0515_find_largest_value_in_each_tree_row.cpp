#include <queue>
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
 * Given the root of a binary tree, return an array of the largest value in each row of the tree
 * (0-indexed).
 *
 * ! The number of nodes in the tree will be in the range [0, 10^4].
 * ! -2^31 <= Node.val <= 2^31 - 1
 */

class Solution {
public:
    std::vector<int> largestValues(TreeNode* root)
    {
        if (!root)
            return {};

        std::queue<TreeNode*> queue;
        queue.push(root);
        std::vector<int> result;
        while (!queue.empty()) {
            int max = INT_MIN;
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                max = std::max(max, node->val);
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(max);
        }
        return result;
    }
};
