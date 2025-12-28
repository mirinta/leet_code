/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 *
 * According to the definition of LCA on Wiki: The lowest common ancestor is defined between two
 * nodes "p" and "q" as the lowest node in "T" that has both "p" and "q" as descendants (where we
 * allow a node to be a descendant of itself).
 *
 * ! The number of nodes in the tree is in the range [2, 10^5].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 * ! p and q will exist in the tree.
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        // p and q are guaranteed in the tree
        // and all values in the tree are unique
        TreeNode* result = nullptr;
        dfs(result, root, p->val, q->val);
        return result;
    }

private:
    // return 2 if the given tree contains both val1 and val2
    // return 1 if the given tree contains val1 or val2
    // return 0 if the given tree doesn't contain val1 and val2
    int dfs(TreeNode*& result, TreeNode* root, int val1, int val2)
    {
        if (!root)
            return 0;

        int count = 0;
        if (root->val == val1 || root->val == val2) {
            count++;
        }
        count += dfs(result, root->left, val1, val2);
        count += dfs(result, root->right, val1, val2);
        if (count == 2 && !result) {
            result = root;
        }
        return count;
    }
};
