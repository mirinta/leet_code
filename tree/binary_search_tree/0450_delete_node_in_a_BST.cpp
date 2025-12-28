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
 * Given a root node reference of a BST and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly) updated of the BST.
 *
 * Basically, the deletion can be divided into two stages:
 *
 * - Search for a node to remove.
 *
 * - If the node is found, delete the node.
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 * ! Each node has a unique value.
 * ! root is a valid binary search tree.
 * ! -10^5 <= key <= 10^5
 */

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key)
    {
        if (!root)
            return nullptr;

        // case 1: key node is in root.right
        if (key > root->val) {
            root->right = deleteNode(root->right, key);
            return root;
        }

        // case 2: key node is in root.left
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
            return root;
        }

        // case 3: current node is the key node
        // case 3.1: key node is a leaf node
        if (!root->left && !root->right)
            return nullptr;

        // case 3.2: key node only has one subtree
        if (!root->left || !root->right)
            return !root->left ? root->right : root->left;

        // case 3.3: replace the root node with a child node X such that
        // X > all nodes of root.left and X < all nodes of root.right
        // since root is a BST, then root.right > root.left
        // thus, X is the min node of root.right
        TreeNode* x = root->right;
        while (x && x->left) {
            x = x->left;
        }
        root->right = deleteNode(root->right, x->val);
        x->left = root->left;
        x->right = root->right;
        return x;
    }
};
