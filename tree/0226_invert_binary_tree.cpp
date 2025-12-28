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
 * Given the "root" of a binary tree, invert the tree, and return its root.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    TreeNode* invertTree(TreeNode* root)
    {
        return approach1(root);
    }

private:
    // DFS, TC = O(N), SC = O(N)
    TreeNode* approach2(TreeNode* root)
    {
        if (!root)
            return nullptr;

        auto* invertedLeft = approach2(root->left);
        auto* invertedRight = approach2(root->right);
        root->left = invertedRight;
        root->right = invertedLeft;
        return root;
    }

    // BFS, TC = O(N), SC = O(N)
    TreeNode* approach1(TreeNode* root)
    {
        if (!root)
            return nullptr;

        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                std::swap(node->left, node->right);
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
        }
        return root;
    }
};