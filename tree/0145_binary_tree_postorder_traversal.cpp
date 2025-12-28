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
 * Given the root of a binary tree, return the postorder traversal of its nodes' values.
 *
 * ! The number of the nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root)
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
        stack.push(root);
        while (!stack.empty()) {
            auto* node = stack.top();
            stack.pop();
            result.push_back(node->val);
            if (node->left) {
                stack.push(node->left);
            }
            if (node->right) {
                stack.push(node->right);
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<int> approach1(TreeNode* root)
    {
        std::vector<int> result;
        postorder(result, root);
        return result;
    }

    void postorder(std::vector<int>& values, TreeNode* node)
    {
        if (!node)
            return;

        postorder(values, node->left);
        postorder(values, node->right);
        values.push_back(node->val);
    }
};