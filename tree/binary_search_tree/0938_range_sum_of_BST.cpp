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
 * Given the root node of a binary search tree and two integers low and high, return the sum of
 * values of all nodes with a value in the inclusive range [low, high].
 *
 * ! The number of nodes in the tree is in the range [1, 2 * 10^4].
 * ! 1 <= Node.val <= 10^5
 * ! 1 <= low <= high <= 10^5
 * ! All Node.val are unique.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        return approach2(root, low, high);
    }

private:
    int approach2(TreeNode* root, int low, int high)
    {
        if (!root)
            return 0;

        int result = 0;
        std::stack<TreeNode*> stack;
        stack.push(root);
        while (!stack.empty()) {
            auto* node = stack.top();
            stack.pop();
            if (node->val >= low && node->val <= high) {
                result += node->val;
            }
            if (node->val > low && node->left) {
                stack.push(node->left);
            }
            if (node->val < high && node->right) {
                stack.push(node->right);
            }
        }
        return result;
    }

    int approach1(TreeNode* root, int low, int high)
    {
        if (!root)
            return 0;

        int sum = 0;
        if (root->val >= low && root->val <= high) {
            sum += root->val;
        }
        if (root->val > low) {
            sum += approach1(root->left, low, high);
        }
        if (root->val < high) {
            sum += approach1(root->right, low, high);
        }
        return sum;
    }
};