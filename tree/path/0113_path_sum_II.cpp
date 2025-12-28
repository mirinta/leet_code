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
 * Given the "root" of a binary tree and an integer "targetSum", return all root-to-leaf paths where
 * the sum of the node values in the path equals "targetSum". Each path should be returned as a list
 * of the node values, not node references.
 *
 * A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf node is
 * a node with no children.
 *
 * ! The number of nodes in the tree is in the range [0, 5000].
 * ! -1000 <= Node.val <= 1000
 * ! -1000 <= targetSum <= 1000
 */

class Solution {
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        dfs(result, path, root, targetSum);
        return result;
    }

private:
    void dfs(std::vector<std::vector<int>>& result, std::vector<int>& path, TreeNode* root, int target)
    {
        if (!root)
            return;

        target -= root->val;
        if (target == 0 && !root->left && !root->right) {
            result.push_back(path);
            result.back().push_back(root->val);
            return;
        }
        path.push_back(root->val);
        dfs(result, path, root->left, target);
        dfs(result, path, root->right, target);
        path.pop_back();
    }
};