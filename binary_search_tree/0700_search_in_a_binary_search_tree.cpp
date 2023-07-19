/**
 Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * You are given the "root" of a binary search tree and integer "val".
 *
 * Find the node in the BST that the node's value equals "val" and return the subtree rooted with
 * that node. If such a node does not exist, return nullptr.
 *
 * ! The number of nodes in the tree is in the range [1, 5000].
 * ! 1 <= Node.val <= 10^7
 * ! root is a binary search tree.
 * ! 1 <= val <= 10^7
 */

class Solution
{
public:
    TreeNode* searchBST(TreeNode* root, int val) { return approach2(root, val); }

private:
    // iteration
    TreeNode* approach2(TreeNode* root, int val)
    {
        auto* i = root;
        while (i) {
            if (i->val > val) {
                i = i->left;
            } else if (i->val < val) {
                i = i->right;
            } else {
                return i;
            }
        }
        return nullptr;
    }

    // recursion
    TreeNode* approach1(TreeNode* root, int val)
    {
        if (!root)
            return nullptr;

        if (root->val > val)
            return approach1(root->left, val);

        if (root->val < val)
            return approach1(root->right, val);

        return root;
    }
};
