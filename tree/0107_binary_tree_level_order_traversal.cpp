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
 * Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values.
 * (i.e., from left to right, level by level from leaf to root).
 *
 * ! The number of nodes in the tree is in the range [0, 2000].
 * ! -1000 <= Node.val <= 1000
 */

class Solution {
public:
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> result;
        std::queue<TreeNode*> queue;
        queue.push(root);
        // level order traversal from top to bottom
        while (!queue.empty()) {
            std::vector<int> values(queue.size(), 0);
            for (auto& val : values) {
                auto* node = queue.front();
                queue.pop();
                val = node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(std::move(values));
        }
        // reverse to get expected result
        std::reverse(result.begin(), result.end());
        return result;
    }
};