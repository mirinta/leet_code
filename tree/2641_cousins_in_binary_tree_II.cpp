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
 * Given the root of a binary tree, replace the value of each node in the tree with the sum of all
 * its cousins' values.
 *
 * Two nodes of a binary tree are cousins if they have the same depth with different parents.
 *
 * Return the root of the modified tree.
 *
 * Note that the depth of a node is the number of edges in the path from the root node to it.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^4
 */

class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        std::queue<std::pair<TreeNode*, int>> queue; // <node, cousinSum>
        queue.emplace(root, root->val);
        std::vector<std::pair<TreeNode*, int>> nodes;
        while (!queue.empty()) {
            const int n = queue.size();
            nodes.resize(n);
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                nodes[i] = queue.front();
                queue.pop();
                auto* node = nodes[i].first;
                sum += node->val;
                if (node->left) {
                    queue.emplace(node->left, node->left->val + (node->right ? node->right->val : 0));
                }
                if (node->right) {
                    queue.emplace(node->right, node->right->val + (node->left ? node->left->val : 0));
                }
            }
            for (const auto& [node, cousinSum] : nodes) {
                node->val = sum - cousinSum;
            }
        }
        return root;
    }
};
