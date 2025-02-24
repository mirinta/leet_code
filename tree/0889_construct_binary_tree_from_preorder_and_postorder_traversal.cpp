#include <functional>
#include <unordered_map>
#include <vector>

/**
 * Definition for a binary tree node.
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
 * Given two integer arrays, preorder and postorder where preorder is the preorder traversal of a
 * binary tree of distinct values and postorder is the postorder traversal of the same tree,
 * reconstruct and return the binary tree.
 *
 * If there exist multiple answers, you can return any of them.
 *
 * ! 1 <= preorder.length <= 30
 * ! 1 <= preorder[i] <= preorder.length
 * ! All the values of preorder are unique.
 * ! postorder.length == preorder.length
 * ! 1 <= postorder[i] <= postorder.length
 * ! All the values of postorder are unique.
 * ! It is guaranteed that preorder and postorder are the preorder traversal and postorder traversal
 * ! of the same binary tree.
 */

class Solution
{
public:
    TreeNode* constructFromPrePost(std::vector<int>& preorder, std::vector<int>& postorder)
    {
        const int n = preorder.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[postorder[i]] = i;
        }
        std::function<TreeNode*(int, int, int, int)> dfs = [&](int lo1, int hi1, int lo2,
                                                               int hi2) -> TreeNode* {
            if (lo1 > hi1)
                return nullptr;

            auto* root = new TreeNode(preorder[lo1]);
            if (lo1 == hi1)
                return root;

            const int leftCount = map[preorder[lo1 + 1]] - lo2 + 1;
            root->left = dfs(lo1 + 1, lo1 + leftCount, lo2, lo2 + leftCount - 1);
            root->right = dfs(lo1 + leftCount + 1, hi1, lo2 + leftCount, hi2 - 1);
            return root;
        };
        return dfs(0, n - 1, 0, n - 1);
    }
};
