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
 * 给定一个有序整数数组，元素各不相同且按升序排列，编写一个算法，创建一棵高度最小的二叉搜索树。
 */

class Solution {
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums)
    {
        return build(0, nums.size() - 1, nums);
    }

private:
    TreeNode* build(int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return nullptr;

        const int mid = lo + (hi - lo) / 2;
        auto* root = new TreeNode(nums[mid]);
        root->left = build(lo, mid - 1, nums);
        root->right = build(mid + 1, hi, nums);
        return root;
    }
};