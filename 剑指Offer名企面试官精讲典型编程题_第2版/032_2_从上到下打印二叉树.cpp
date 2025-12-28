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
 *
 * ! 本题与LC 102相同。
 */

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> result;
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            const auto size = queue.size();
            std::vector<int> values(size);
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
        return result;
    }
};
