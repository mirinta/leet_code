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
 * Given an integer "n", return all the structurally unique BST's, which has exactly "n" nodes of
 * unique values from "1" to "n". Return the answer in any order.
 */

class Solution {
public:
    std::vector<TreeNode*> generateTrees(int n)
    {
        return build(1, n);
    }

private:
    std::vector<TreeNode*> build(int low, int high)
    {
        if (low > high)
            return {nullptr};

        std::vector<TreeNode*> result;
        for (int i = low; i <= high; ++i) {
            // use i as root node
            const auto leftSubtrees = build(low, i - 1);
            const auto rightSubtrees = build(i + 1, high);
            for (auto* const left : leftSubtrees) {
                for (auto* const right : rightSubtrees) {
                    auto* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        return result;
    }
};
