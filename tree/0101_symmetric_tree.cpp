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
 * Given the "root" of a binary tree, check whether it is a mirror of itself (i.e., symmetric around
 * its center).
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    bool isSymmetric(TreeNode* root)
    {
        return approach2(root);
    }

private:
    // BFS, TC = O(N), SC = O(N)
    bool approach2(TreeNode* root)
    {
        if (!root)
            return false;

        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            std::vector<int> values(queue.size());
            for (auto& val : values) {
                auto* node = queue.front();
                queue.pop();
                val = node ? node->val : INT_MIN;
                if (node) {
                    queue.push(node->left);
                    queue.push(node->right);
                }
            }
            for (int i = 0, j = values.size() - 1; i < j; ++i, --j) {
                if (values[i] != values[j])
                    return false;
            }
        }
        return true;
    }

    // DFS, TC = O(N), SC = O(N)
    bool approach1(TreeNode* root)
    {
        if (!root)
            return false;

        return dfs(root->left, root->right);
    }

    bool dfs(TreeNode* node1, TreeNode* node2)
    {
        if (!node1 && !node2)
            return true;

        if (!node1 || !node2)
            return false;

        if (node1->val != node2->val)
            return false;

        return dfs(node1->left, node2->right) && dfs(node1->right, node2->left);
    }
};