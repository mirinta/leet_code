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
 * Given two integer arrays "inorder" and "postorder" where "inorder" is the inorder traversal of a
 * binary tree and "postorder" is the postorder traversal of the same tree, construct and return the
 * binary tree.
 *
 * ! 1 <= inorder.length <= 3000
 * ! postorder.length == inorder.length
 * ! -3000 <= inorder[i], postorder[i] <= 3000
 * ! inorder and postorder consist of unique values.
 * ! Each value of postorder also appears in inorder.
 * ! inorder is guaranteed to be the inorder traversal of the tree.
 * ! postorder is guaranteed to be the postorder traversal of the tree.
 */

class Solution {
public:
    TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder)
    {
        /**
         *        3
         *     /     \
         *    9       8
         *   / \     / \
         *  1   5   6   7
         * / \ / \ / \ / \
         *
         *      index: 0  1  2  3  4  5  6
         *    inorder: 1  9  5  3  6  8  7
         *             |LEFT |  ^  |RIGHT|
         *
         *      index: 0  1  2  3  4  5  6
         *  postorder: 1  5  9  6  7  8  3
         *             |LEFT |  |RIGHT|  ^
         */
        const int n = inorder.size();
        for (int i = 0; i < n; ++i) {
            map[inorder[i]] = i;
        }
        return build(inorder, 0, n - 1, postorder, 0, n - 1);
    }

private:
    std::unordered_map<int, int> map; // val to index of inorder

    TreeNode*
        build(const std::vector<int>& inorder, int lo1, int hi1, const std::vector<int>& postorder, int lo2, int hi2)
    {
        if (lo1 > hi1)
            return nullptr;

        auto* root = new TreeNode(postorder[hi2]);
        const int rootIdx = map[root->val];
        const int numOfLeft = rootIdx - lo1;
        root->left = build(inorder, lo1, rootIdx - 1, postorder, lo2, lo2 + numOfLeft - 1);
        root->right = build(inorder, rootIdx + 1, hi1, postorder, lo2 + numOfLeft, hi2 - 1);
        return root;
    }
};