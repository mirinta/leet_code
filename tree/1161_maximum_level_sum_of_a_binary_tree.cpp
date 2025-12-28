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
 * Given the "root" of a binary tree, the level of its root is 1, the level of its children is 2,
 * and so on.
 *
 * Return the smallest level "x" such that the sum of all the values of nodes at level "x" is
 * maximal.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 */

class Solution {
public:
    int maxLevelSum(TreeNode* root)
    {
        if (!root)
            return 0;

        std::queue<TreeNode*> queue;
        queue.push(root);
        int maxSum = INT_MIN;
        int minLevel = 0;
        int currentLevel = 0;
        while (!queue.empty()) {
            currentLevel++;
            const auto size = queue.size();
            int currentSum = 0;
            for (size_t k = 0; k < size; ++k) {
                auto* node = queue.front();
                queue.pop();
                currentSum += node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            if (currentSum > maxSum) {
                maxSum = currentSum;
                minLevel = currentLevel;
            }
        }
        return minLevel;
    }
};
