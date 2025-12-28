#include <functional>
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
 * Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the
 * most frequently occurred element) in it.
 *
 * If the tree has more than one mode, return them in any order.
 *
 * Assume a BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than or equal to the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than or equal to the node's
 * key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -10^5 <= Node.val <= 10^5
 *
 * ! Could you do that without using any extra space?
 * ! Assume that the implicit stack space incurred due to recursion does not count.
 */

class Solution {
public:
    std::vector<int> findMode(TreeNode* root)
    {
        std::vector<int> result;
        int maxFreq = 0;
        int currVal = INT_MIN;
        int currFreq = 0;
        std::function<void(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root)
                return;

            dfs(root->left);
            if (root->val == currVal) {
                currFreq++;
            } else {
                currVal = root->val;
                currFreq = 1;
            }
            if (currFreq > maxFreq) {
                maxFreq = currFreq;
                result.clear();
                result.push_back(root->val);
            } else if (currFreq == maxFreq) {
                result.push_back(root->val);
            }
            dfs(root->right);
        };
        dfs(root);
        return result;
    }
};
