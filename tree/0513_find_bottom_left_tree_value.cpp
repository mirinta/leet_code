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
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -2^31 <= Node.val <= 2^31 - 1
 */

class Solution {
public:
    int findBottomLeftValue(TreeNode* root)
    {
        return approach2(root);
    }

private:
    // DFS, TC = O(N), SC = O(N)
    int approach2(TreeNode* root)
    {
        int result = INT_MIN;
        int maxDepth = INT_MIN;
        dfs(result, maxDepth, root, 0);
        return result;
    }

    void dfs(int& result, int& maxDepth, TreeNode* root, int depth)
    {
        if (!root)
            return;

        if (depth > maxDepth) {
            maxDepth = depth;
            result = root->val;
        }
        dfs(result, maxDepth, root->left, depth + 1);
        dfs(result, maxDepth, root->right, depth + 1);
    }

    // BFS, TC = O(N), SC = O(N)
    int approach1(TreeNode* root)
    {
        std::queue<TreeNode*> queue;
        queue.push(root);
        int result = INT_MIN;
        while (!queue.empty()) {
            result = queue.front()->val;
            for (int k = queue.size(); k > 0; --k) {
                auto* node = queue.front();
                queue.pop();
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
