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
 * 从左向右遍历一个数组，通过不断将其中的元素插入树中可以逐步地生成一棵二叉搜索树。
 *
 * 给定一个由不同节点组成的二叉搜索树 root，输出所有可能生成此树的数组。
 *
 * ! 二叉搜索树中的节点数在 [0, 1000] 的范围内
 * ! 1 <= 节点值 <= 10^6
 * ! 用例保证符合要求的数组数量不超过 5000
 */

class Solution {
public:
    std::vector<std::vector<int>> BSTSequences(TreeNode* root)
    {
        if (!root)
            return {{}};

        const auto sequences1 = BSTSequences(root->left);
        const auto sequences2 = BSTSequences(root->right);
        std::vector<std::vector<int>> result;
        std::vector<int> path{root->val};
        for (const auto& seq1 : sequences1) {
            for (const auto& seq2 : sequences2) {
                std::vector<std::vector<int>> merged;
                backtrack(merged, path, seq1, 0, seq2, 0);
                result.insert(result.end(), merged.begin(), merged.end());
            }
        }
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& merged,
                   std::vector<int>& path,
                   const std::vector<int>& seq1,
                   int i1,
                   const std::vector<int>& seq2,
                   int i2)
    {
        if (i1 == seq1.size() || i2 == seq2.size()) {
            merged.push_back(path);
            merged.back().insert(merged.back().end(), seq1.begin() + i1, seq1.end());
            merged.back().insert(merged.back().end(), seq2.begin() + i2, seq2.end());
            return;
        }
        path.push_back(seq1[i1]);
        backtrack(merged, path, seq1, i1 + 1, seq2, i2);
        path.pop_back();
        path.push_back(seq2[i2]);
        backtrack(merged, path, seq1, i1, seq2, i2 + 1);
        path.pop_back();
    }
};