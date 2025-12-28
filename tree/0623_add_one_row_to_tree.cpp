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
 * Given the root of a binary tree and two integers val and depth, add a row of nodes with value val
 * at the given depth depth.
 *
 * Note that the root node is at depth 1.
 *
 * The adding rule is:
 *
 * - Given the integer depth, for each not null tree node cur at the depth depth - 1, create two
 * tree nodes with value val as cur's left subtree root and right subtree root.
 *
 * - cur's original left subtree should be the left subtree of the new left subtree root.
 *
 * - cur's original right subtree should be the right subtree of the new right subtree root.
 *
 * - If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value
 * val as the new root of the whole original tree, and the original tree is the new root's left
 * subtree.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! The depth of the tree is in the range [1, 10^4].
 * ! -100 <= Node.val <= 100
 * ! -10^5 <= val <= 10^5
 * ! 1 <= depth <= the depth of tree + 1
 */

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth)
    {
        return approach2(root, val, depth);
    }

private:
    TreeNode* approach2(TreeNode* root, int val, int depth)
    {
        if (depth == 1) {
            auto* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        std::queue<TreeNode*> queue;
        queue.push(root);
        int currDepth = 1;
        while (currDepth++ < depth - 1 && !queue.empty()) {
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
        while (!queue.empty()) {
            auto* node = queue.front();
            queue.pop();
            auto* left = node->left;
            auto* right = node->right;
            node->left = new TreeNode(val);
            node->left->left = left;
            node->right = new TreeNode(val);
            node->right->right = right;
        }
        return root;
    }

    TreeNode* approach1(TreeNode* root, int val, int depth)
    {
        if (depth == 1) {
            auto* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        return dfs(root, 1, val, depth);
    }

    TreeNode* dfs(TreeNode* root, int depth, int val, int targetDepth)
    {
        if (!root)
            return nullptr;

        auto* left = dfs(root->left, depth + 1, val, targetDepth);
        auto* right = dfs(root->right, depth + 1, val, targetDepth);
        if (depth == targetDepth - 1) {
            root->left = new TreeNode(val);
            root->left->left = left;
            root->right = new TreeNode(val);
            root->right->right = right;
        }
        return root;
    }
};