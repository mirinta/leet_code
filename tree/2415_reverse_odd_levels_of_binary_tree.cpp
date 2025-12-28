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
 * Given the root of a perfect binary tree, reverse the node values at each odd level of the tree.
 *
 * For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18], then it should become
 * [18,29,11,7,4,3,1,2]. Return the root of the reversed tree.
 *
 * A binary tree is perfect if all parent nodes have two children and all leaves are on the same
 * level.
 *
 * The level of a node is the number of edges along the path between it and the root node.
 *
 * ! The number of nodes in the tree is in the range [1, 2^14].
 * ! 0 <= Node.val <= 10^5
 * ! root is a perfect binary tree.
 */

class Solution {
public:
    TreeNode* reverseOddLevels(TreeNode* root)
    {
        if (!root)
            return nullptr;

        std::queue<TreeNode*> queue;
        queue.push(root);
        std::vector<TreeNode*> nodes;
        int level = 0;
        while (!queue.empty()) {
            const bool isOdd = level % 2;
            if (isOdd) {
                nodes.clear();
                nodes.reserve(queue.size());
            }
            for (int k = queue.size(); k > 0; --k) {
                auto* node = queue.front();
                queue.pop();
                if (isOdd) {
                    nodes.push_back(node);
                }
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            for (int i = 0, j = nodes.size() - 1; i < j && isOdd; ++i, --j) {
                std::swap(nodes[i]->val, nodes[j]->val);
            }
            level++;
        }
        return root;
    }
};