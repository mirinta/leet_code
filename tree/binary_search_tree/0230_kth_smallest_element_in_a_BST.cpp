#include <stack>

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
 * Given the "root" of a binary search tree, and an integer "k", return the "k"th smallest value
 * (1-indexed) of all the values of the nodes in the tree.
 *
 * ! The number of nodes in the tree is "n".
 * ! 1 <= k <= n
 * ! 0 <= Node.val <= 10^4
 */

class Solution {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        return approach2(root, k);
    }

private:
    // in-order traversal, recursive, time O(N), space O(N)
    int approach1(TreeNode* root, int k)
    {
        int result = -1;
        dfs(result, k, root);
        return result;
    }

    void dfs(int& result, int& k, TreeNode* root)
    {
        if (!root)
            return;

        dfs(result, k, root->left);
        if (--k == 0) {
            result = root->val;
            return;
        }
        dfs(result, k, root->right);
    }

    // in-order traversal, iterative, time O(N), space O(N)
    int approach2(TreeNode* root, int k)
    {
        if (!root)
            return -1;

        std::stack<TreeNode*> stack;
        auto* node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            if (--k == 0)
                return stack.top()->val;

            node = stack.top()->right;
            stack.pop();
        }
        return -1;
    }
};
