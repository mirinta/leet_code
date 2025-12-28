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
 * 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，
 * 第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
 *
 * ! 节点总数 <= 1000
 */

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root)
    {
        if (!root)
            return {};

        std::queue<TreeNode*> queue;
        queue.push(root);
        bool reverse = false;
        std::vector<std::vector<int>> result;
        while (!queue.empty()) {
            const size_t size = queue.size();
            std::vector<int> values(size);
            for (size_t i = 0; i < size; ++i) {
                auto* node = queue.front();
                queue.pop();
                values[reverse ? size - i - 1 : i] = node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            reverse = !reverse;
            result.push_back(std::move(values));
        }
        return result;
    }
};