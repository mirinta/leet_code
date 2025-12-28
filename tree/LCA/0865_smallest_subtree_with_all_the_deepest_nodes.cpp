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
 * Given the root of a binary tree, the depth of each node is the shortest distance to the root.
 *
 * Return the smallest subtree such that it contains all the deepest nodes in the original tree.
 *
 * A node is called the deepest if it has the largest depth possible among any node in the entire
 * tree.
 *
 * The subtree of a node is a tree consisting of that node, plus the set of all descendants of that
 * node.
 *
 * ! This question is the same as LC.1123.
 *
 * ! The number of nodes in the tree will be in the range [1, 500].
 * ! T0 <= Node.val <= 500
 * ! The values of the nodes in the tree are unique.
 */

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root)
    {
        if (!root)
            return nullptr;

        preorder(root, 0);
        for (const auto& [val, depth] : map) {
            if (depth == maxDepth) {
                numOfDeepestLeaves++;
            }
        }
        postorder(root);
        return result;
    }

private:
    TreeNode* result = nullptr;
    int maxDepth = 0;
    int numOfDeepestLeaves = 0;
    std::unordered_map<int, int> map; // val to depth, use vals as keys because Node.val are unique

    void preorder(TreeNode* root, int depth)
    {
        if (!root)
            return;

        map[root->val] = depth;
        maxDepth = std::max(maxDepth, depth);
        preorder(root->left, depth + 1);
        preorder(root->right, depth + 1);
    }

    int postorder(TreeNode* root)
    {
        if (!root)
            return 0;

        int count = map[root->val] == maxDepth ? 1 : 0;
        count += postorder(root->left);
        count += postorder(root->right);
        if (count == numOfDeepestLeaves && !result) {
            result = root;
        }
        return count;
    }
};