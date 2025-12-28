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
 * Consider all the leaves of a binary tree, from left to right order, the values of those leaves
 * form a leaf value sequence.
 *
 * Two binary trees are considered leaf-similar if their leaf value sequence is the same.
 *
 * Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.
 *
 * ! The number of nodes in each tree will be in the range [1, 200].
 * ! Both of the given trees will have values in the range [0, 200].
 */

class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2)
    {
        std::vector<int> leaves1;
        preorder(leaves1, root1);
        std::vector<int> leaves2;
        preorder(leaves2, root2);
        return leaves1 == leaves2;
    }

private:
    void preorder(std::vector<int>& leaves, TreeNode* root)
    {
        if (!root)
            return;

        if (!root->left && !root->right) {
            leaves.push_back(root->val);
            return;
        }
        preorder(leaves, root->left);
        preorder(leaves, root->right);
    }
};