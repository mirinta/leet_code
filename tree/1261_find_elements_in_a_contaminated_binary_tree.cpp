#include <queue>
#include <unordered_set>

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
 * Given a binary tree with the following rules:
 *
 * 1. root.val == 0
 *
 * 2. For any treeNode:
 *
 * - If treeNode.val has a value x and treeNode.left != null, then treeNode.left.val == 2 * x + 1
 *
 * - If treeNode.val has a value x and treeNode.right != null, then treeNode.right.val == 2 * x + 2
 *
 *
 * Now the binary tree is contaminated, which means all treeNode.val have been changed to -1.
 *
 * Implement the FindElements class:
 *
 * - FindElements(TreeNode* root) Initializes the object with a contaminated binary tree and
 * recovers it.
 *
 * - bool find(int target) Returns true if the target value exists in the recovered binary tree.
 *
 * ! TreeNode.val == -1
 * ! The height of the binary tree is less than or equal to 20
 * ! The total number of nodes is between [1, 10^4]
 * ! Total calls of find() is between [1, 10^4]
 * ! 0 <= target <= 10^6
 */

class FindElements {
public:
    FindElements(TreeNode* root)
    {
        root->val = 0;
        values.insert(0);
        std::queue<TreeNode*> queue;
        queue.emplace(root);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                auto* const node = queue.front();
                queue.pop();
                if (node->left) {
                    node->left->val = 2 * node->val + 1;
                    values.insert(node->left->val);
                    queue.emplace(node->left);
                }
                if (node->right) {
                    node->right->val = 2 * node->val + 2;
                    values.insert(node->right->val);
                    queue.emplace(node->right);
                }
            }
        }
    }

    bool find(int target)
    {
        return values.count(target);
    }

private:
    std::unordered_set<int> values;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
