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
 * Given the roots of two binary trees root and subRoot, return true if there is a subtree of root
 * with the same structure and node values of subRoot and false otherwise.
 *
 * A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's
 * descendants. The tree tree could also be considered as a subtree of itself.
 *
 * ! The number of nodes in the root tree is in the range [1, 2000].
 * ! The number of nodes in the subRoot tree is in the range [1, 1000].
 * ! -10^4 <= root.val <= 10^4
 * ! -10^4 <= subRoot.val <= 10^4
 */

class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot)
    {
        if (!root && !subRoot)
            return true;

        if (!root || !subRoot)
            return false;

        if (dfs(root, subRoot))
            return true;

        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }

private:
    // return whether the given two trees are exactly the same
    bool dfs(TreeNode* node1, TreeNode* node2)
    {
        if (!node1 && !node2)
            return true;

        if (!node1 || !node2 || node1->val != node2->val)
            return false;

        return dfs(node1->left, node2->left) && dfs(node1->right, node2->right);
    }
};