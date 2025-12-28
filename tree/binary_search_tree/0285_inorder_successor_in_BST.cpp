/**
 Definition for a binary tree node.
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
 * Given the root of a binary search tree and a node p in it, return the in-order successor of that
 * node in the BST. If the given node has no in-order successor in the tree, return null.
 *
 * The successor of a node p is the node with the smallest key greater than p.val.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! All Nodes will have unique values.
 */

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
    {
        TreeNode* result = nullptr;
        while (root) {
            if (p->val >= root->val) {
                root = root->right;
            } else {
                result = root;
                root = root->left;
            }
        }
        return result;
    }
};