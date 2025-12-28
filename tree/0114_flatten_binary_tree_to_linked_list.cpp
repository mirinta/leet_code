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
 * Given the "root" of a binary tree, flatten the tree into a "linked list":
 *
 * - The "linked list" should use the same "TreeNode" class there the "right" child pointer points
 * to the next node in the list and the "left" child pointer is always nullptr.
 *
 * - The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 *
 * ! The number of nodes in the tree is in the range [0, 2000].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    void flatten(TreeNode* root)
    {
        approach2(root);
    }

private:
    // Post-order
    void approach2(TreeNode* root)
    {
        if (!root)
            return;

        approach2(root->left);  // left subtree is flattened, 2->3->4
        approach2(root->right); // right subtree is flattened, 5->6
        auto* leftHead = root->left;
        auto* rightHead = root->right;
        root->left = nullptr;
        root->right = leftHead;
        auto* leftTail = root;
        while (leftTail && leftTail->right) {
            leftTail = leftTail->right;
        }
        leftTail->right = rightHead;
    }

    // Pre-order
    void approach1(TreeNode* root)
    {
        if (!root)
            return;

        TreeNode vHead(0);
        auto* node = &vHead;
        std::stack<TreeNode*> stack;
        stack.push(root);
        while (!stack.empty()) {
            auto* top = stack.top();
            stack.pop();
            if (top->right) {
                stack.push(top->right);
            }
            if (top->left) {
                stack.push(top->left);
                top->left = nullptr;
            }
            node->right = top;
            node = node->right;
        }
    }
};