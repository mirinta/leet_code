#include <functional>

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
 * 实现一个函数，检查一棵二叉树是否为二叉搜索树。
 */

class Solution {
public:
    bool isValidBST(TreeNode* root)
    {
        return approach1(root);
    }

private:
    using LL = long long;

    bool approach3(TreeNode* root)
    {
        std::function<std::pair<LL, LL>(TreeNode*)> dfs = [&dfs](TreeNode* root) {
            if (!root)
                return std::make_pair(LLONG_MAX, LLONG_MIN);

            const auto [leftMin, leftMax] = dfs(root->left);
            const auto [rightMin, rightMax] = dfs(root->right);
            const LL val = root->val;
            if (leftMax >= val || val >= rightMin)
                return std::make_pair(LLONG_MIN, LLONG_MAX);

            return std::make_pair(std::min(leftMin, val), std::max(rightMax, val));
        };
        return dfs(root).first != LLONG_MIN;
    }

    bool approach2(TreeNode* root)
    {
        std::function<bool(TreeNode*, LL, LL)> dfs = [&dfs](TreeNode* root, LL min, LL max) {
            if (!root)
                return true;

            if (min >= root->val || root->val >= max)
                return false;

            return dfs(root->left, min, root->val) && dfs(root->right, root->val, max);
        };
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }

    bool approach1(TreeNode* root)
    {
        std::function<bool(LL&, TreeNode*)> dfs = [&dfs](LL& prev, TreeNode* root) {
            if (!root)
                return true;

            const bool left = dfs(prev, root->left);
            if (!left || prev >= root->val)
                return false;

            prev = root->val;
            const bool right = dfs(prev, root->right);
            return right;
        };
        LL prev = LLONG_MIN;
        return dfs(prev, root);
    }
};