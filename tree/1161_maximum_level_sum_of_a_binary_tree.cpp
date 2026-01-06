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
        queue.emplace(root);
        int level = 0;
        int result = 0;
        int max = INT_MIN;
        while (!queue.empty()) {
            level++;
            int sum = 0;
            for (int k = queue.size(); k > 0; --k) {
                auto node = queue.front();
                queue.pop();
                sum += node->val;
                if (node->left) {
                    queue.emplace(node->left);
                }
                if (node->right) {
                    queue.emplace(node->right);
                }
            }
            if (sum > max) {
                max = sum;
                result = level;
            }
        }
        return result;
    }
};
