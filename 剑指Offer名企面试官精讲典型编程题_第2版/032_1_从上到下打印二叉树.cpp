#include <queue>
#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
 *
 * ! 节点总数 <= 1000
 */

class Solution {
public:
    std::vector<int> levelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            const auto size = queue.size();
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                result.push_back(node->val);
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
        }
        return result;
    }
};