#include <unordered_map>
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
 * Given two integer arrays "preorder" and "inorder" where "preorder" is the preorder traversal of a
 * binary tree and "inorder" is the inorder traversal of the same tree, construct and return the
 * binary tree.
 *
 * ! 1 <= preorder.length <= 3000
 * ! inorder.length == preorder.length
 * ! -3000 <= preorder[i], inorder[i] <= 3000
 * ! preorder and inorder consist of unique values.
 * ! Each value of inorder also appears in preorder.
 * ! preorder is guaranteed to be the preorder traversal of the tree.
 * ! inorder is guaranteed to be the inorder traversal of the tree.
 */

class Solution {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
    {
        /**
         *        3
         *     /     \
         *    9       8
         *   / \     / \
         *  1   5   6   7
         * / \ / \ / \ / \
         *
         *    index: 0  1  2  3  4  5  6
         * preorder: 3  9  1  5  8  6  7
         *           ^  |LEFT |  |RIGHT|
         *
         *    index: 0  1  2  3  4  5  6
         *  inorder: 1  9  5  3  6  8  7
         *           |LEFT |  ^  |RIGHT|
         */
        const int n = preorder.size();
        for (int i = 0; i < n; ++i) {
            map[inorder[i]] = i;
        }
        return build(preorder, 0, n - 1, inorder, 0, n - 1);
    }

private:
    std::unordered_map<int, int> map; // val to index of inorder

    TreeNode*
        build(const std::vector<int>& preorder, int lo1, int hi1, const std::vector<int>& inorder, int lo2, int hi2)
    {
        if (lo1 > hi1)
            return nullptr;

        auto* root = new TreeNode(preorder[lo1]);
        const int rootIdx = map[root->val];
        const int numOfLeft = rootIdx - lo2;
        root->left = build(preorder, lo1 + 1, lo1 + numOfLeft, inorder, lo2, rootIdx - 1);
        root->right = build(preorder, lo1 + 1 + numOfLeft, hi1, inorder, rootIdx + 1, hi2);
        return root;
    }
};