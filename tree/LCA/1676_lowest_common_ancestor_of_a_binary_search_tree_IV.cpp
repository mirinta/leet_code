#include <unordered_set>
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
 * Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common
 * ancestor (LCA) of all the nodes in nodes. All the nodes will exist in the tree, and all values of
 * the tree's nodes are unique.
 *
 * Extending the definition of LCA on Wikipedia: "The lowest common ancestor of n nodes p1, p2, ...,
 * pn in a binary tree T is the lowest node that has every pi as a descendant (where we allow a node
 * to be a descendant of itself) for every valid i". A descendant of a node x is a node y that is on
 * the path from node x to some leaf node.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! All nodes[i] will exist in the tree.
 * ! All nodes[i] are distinct.
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, std::vector<TreeNode*>& nodes)
    {
        if (!root || nodes.empty())
            return nullptr;

        // #NOTE# Node.val are unique
        std::unordered_set<int> values;
        for (auto* node : nodes) {
            values.insert(node->val);
        }
        dfs(root, values);
        return result;
    }

private:
    TreeNode* result = nullptr;

    // return the num of target nodes exist in "root"
    int dfs(TreeNode* root, const std::unordered_set<int>& values)
    {
        if (!root)
            return 0;

        int count = values.count(root->val) ? 1 : 0;
        count += dfs(root->left, values);
        count += dfs(root->right, values);
        if (count == values.size() && !result) {
            result = root;
        }
        return count;
    }
};
