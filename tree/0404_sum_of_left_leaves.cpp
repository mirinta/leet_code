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
 * Given the root of a binary tree, return the sum of all left leaves.
 *
 * A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! -1000 <= Node.val <= 1000
 */

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root)
    {
        int result = 0;
        dfs(result, root, false);
        return result;
    }

private:
    void dfs(int& result, TreeNode* root, bool isLeftChild)
    {
        if (!root)
            return;

        if (isLeftChild && !root->left && !root->right) {
            result += root->val;
            return;
        }
        dfs(result, root->left, true);
        dfs(result, root->right, false);
    }
};