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
 * In a binary tree, a lonely node is a node that is the only child of its parent node. The root of
 * the tree is not lonely because it does not have a parent node.
 *
 * Given the root of a binary tree, return an array containing the values of all lonely nodes in the
 * tree. Return the list in any order.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! 1 <= Node.val <= 10^6
 */

class Solution {
public:
    std::vector<int> getLonelyNodes(TreeNode* root)
    {
        std::vector<int> result;
        dfs(result, root, false);
        return result;
    }

private:
    void dfs(std::vector<int>& result, TreeNode* root, bool isAlone)
    {
        if (!root)
            return;

        if (isAlone) {
            result.push_back(root->val);
        }
        dfs(result, root->left, !root->right);
        dfs(result, root->right, !root->left);
    }
};