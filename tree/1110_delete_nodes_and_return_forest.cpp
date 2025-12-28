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
 * Given the root of a binary tree, each node in the tree has a distinct value.
 *
 * After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union
 * of trees).
 *
 * Return the roots of the trees in the remaining forest. You may return the result in any order.
 *
 * ! The number of nodes in the given tree is at most 1000.
 * ! Each node has a distinct value between 1 and 1000.
 * ! to_delete.length <= 1000
 * ! to_delete contains distinct values between 1 and 1000.
 */

class Solution {
public:
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete)
    {
        if (!root)
            return {};

        std::unordered_set<int> toDelete(to_delete.begin(), to_delete.end());
        std::vector<TreeNode*> result;
        if (dfs(result, root, toDelete)) {
            result.push_back(root);
        }
        return result;
    }

private:
    TreeNode* dfs(std::vector<TreeNode*>& result, TreeNode* root, const std::unordered_set<int>& toDelete)
    {
        if (!root)
            return nullptr;

        root->left = dfs(result, root->left, toDelete);
        root->right = dfs(result, root->right, toDelete);
        if (toDelete.find(root->val) == toDelete.end())
            return root; // this root is not deleted

        // otherwise, there maybe two separate trees
        if (root->left) {
            result.push_back(root->left);
        }
        if (root->right) {
            result.push_back(root->right);
        }
        return nullptr;
    }
};
