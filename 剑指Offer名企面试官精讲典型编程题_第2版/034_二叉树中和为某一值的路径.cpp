#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * 给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点
 * 路径总和等于给定目标和的路径。
 *
 * 叶子节点 是指没有子节点的节点。
 *
 * ! 树中节点总数在范围 [0, 5000] 内
 * ! -1000 <= Node.val <= 1000
 * ! -1000 <= targetSum <= 1000
 *
 * ! 本题与LC 113相同。
 */

class Solution {
public:
    std::vector<std::vector<int>> pathSum(TreeNode* root, int target)
    {
        if (!root)
            return {};

        std::vector<int> path;
        traverse(path, root, target);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void traverse(std::vector<int> path, TreeNode* node, int target)
    {
        if (!node)
            return;

        if (node->val == target && !node->left && !node->right) {
            result.push_back(path);
            result.back().push_back(node->val);
        }
        path.push_back(node->val);
        traverse(path, node->left, target - node->val);
        traverse(path, node->right, target - node->val);
        path.pop_back();
    }
};