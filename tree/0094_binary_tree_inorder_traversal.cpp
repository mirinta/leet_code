#include <stack>
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
 * Given the "root" of a binary tree, return the inorder traversal of its nodes' values.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        return approach2(root);
    }

private:
    std::vector<int> approach2(TreeNode* root)
    {
        if (!root)
            return {};

        std::vector<int> result;
        std::stack<TreeNode*> stack;
        auto* curr = root;
        while (curr || !stack.empty()) {
            while (curr) {
                stack.push(curr);
                curr = curr->left;
            }
            auto* node = stack.top();
            stack.pop();
            result.push_back(node->val);
            curr = node->right;
        }
        return result;
    }

    std::vector<int> approach1(TreeNode* root)
    {
        std::vector<int> result;
        inorder(result, root);
        return result;
    }

    void inorder(std::vector<int>& values, TreeNode* node)
    {
        if (!node)
            return;

        inorder(values, node->left);
        values.push_back(node->val);
        inorder(values, node->right);
    }
};
