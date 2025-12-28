/**
 Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p
 * and q. If either node p or q does not exist in the tree, return null. All values of the nodes in
 * the tree are unique.
 *
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q
 * in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node
 * to be a descendant of itself)". A descendant of a node x is a node y that is on the path from
 * node x to some leaf node.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || !p || !q)
            return nullptr;

        dfs(root, p->val, q->val);
        return result;
    }

private:
    TreeNode* result = nullptr;

    // return 0: both val1 and val2 doesn't exist in "root"
    // return 1: either val1 or val2 exists in "root"
    // return 2: both val1 and val2 exist in "root"
    // #NOTE# val1 != val2
    int dfs(TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        int count = root->val == val1 || root->val == val2 ? 1 : 0;
        count += dfs(root->left, val1, val2);
        count += dfs(root->right, val1, val2);
        if (count == 2 && !result) {
            result = root;
        }
        return count;
    }
};
