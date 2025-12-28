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
 * Given an array of integers preorder, which represents the preorder traversal of a BST (i.e.,
 * binary search tree), construct the tree and return its root.
 *
 * It is guaranteed that there is always possible to find a binary search tree with the given
 * requirements for the given test cases.
 *
 * A binary search tree is a binary tree where for every node, any descendant of Node.left has a
 * value strictly less than Node.val, and any descendant of Node.right has a value strictly greater
 * than Node.val.
 *
 * A preorder traversal of a binary tree displays the value of the node first, then traverses
 * Node.left, then traverse Node.right.
 *
 * ! All the values of preorder are unique.
 */

class Solution {
public:
    TreeNode* bstFromPreorder(const std::vector<int>& preorder)
    {
        if (preorder.empty())
            return nullptr;

        return build(0, preorder.size() - 1, preorder);
    }

private:
    TreeNode* build(int startPreorder, int endPreorder, const std::vector<int>& preorder)
    {
        if (startPreorder > endPreorder)
            return nullptr;

        const int rootVal = preorder[startPreorder];
        auto* root = new TreeNode(rootVal);
        int indexOfFirstGreater = startPreorder;
        while (indexOfFirstGreater < preorder.size() && preorder[indexOfFirstGreater] <= rootVal) {
            indexOfFirstGreater++;
        }
        root->left = build(startPreorder + 1, indexOfFirstGreater - 1, preorder);
        root->right = build(indexOfFirstGreater, endPreorder, preorder);
        return root;
    }
};