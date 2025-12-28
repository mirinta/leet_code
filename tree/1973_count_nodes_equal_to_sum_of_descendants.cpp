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
 * Given the root of a binary tree, return the number of nodes where the value of the node is equal
 * to the sum of the values of its descendants.
 *
 * A descendant of a node x is any node that is on the path from node x to some leaf node. The sum
 * is considered to be 0 if the node has no descendants.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 0 <= Node.val <= 10^5
 */

class Solution {
public:
    int equalToDescendants(TreeNode* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return the sum of all nodes of the given tree
    long long dfs(int& result, TreeNode* root)
    {
        if (!root)
            return 0;

        const long long leftSum = dfs(result, root->left);
        const long long rightSum = dfs(result, root->right);
        if (root->val == leftSum + rightSum) {
            result++;
        }
        return root->val + leftSum + rightSum;
    }
};