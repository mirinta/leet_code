#include <functional>
#include <unordered_map>

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
 * Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
 *
 * Recall that:
 *
 * - The node of a binary tree is a leaf if and only if it has no children.
 *
 * - The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its
 * children is d + 1.
 *
 * - The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that
 * every node in S is in the subtree with root A.
 *
 * ! This question is the same as LC.865.
 *
 * ! The number of nodes in the tree will be in the range [1, 1000].
 * ! 0 <= Node.val <= 1000
 * ! The values of the nodes in the tree are unique.
 */

class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root)
    {
        if (!root)
            return nullptr;

        std::unordered_map<int, int> valToDepth;
        std::unordered_map<int, int> depthToCount;
        int maxDepth = 0;
        std::function<void(TreeNode*, int)> preorder = [&](TreeNode* node, int depth) {
            if (!node)
                return;

            valToDepth[node->val] = depth;
            depthToCount[depth]++;
            maxDepth = std::max(maxDepth, depth);
            preorder(node->left, depth + 1);
            preorder(node->right, depth + 1);
        };
        preorder(root, 0);
        TreeNode* result = nullptr;
        std::function<int(TreeNode*)> postorder = [&](TreeNode* node) {
            if (!node)
                return 0;

            int count = valToDepth[node->val] == maxDepth;
            count += postorder(node->left);
            count += postorder(node->right);
            if (count == depthToCount[maxDepth] && !result) {
                result = node;
            }
            return count;
        };
        postorder(root);
        return result;
    }
};