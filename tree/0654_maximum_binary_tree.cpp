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
 * You are given an integer array nums with no duplicates. A maximum binary tree can be built
 * recursively from nums using the following algorithm:
 *
 * 1. Create a root node whose value is the maximum value in nums.
 *
 * 2. Recursively build the left subtree on the subarray prefix to the left of the maximum value.
 *
 * 3. Recursively build the right subtree on the subarray suffix to the right of the maximum value.
 *
 * Return the maximum binary tree built from nums.
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 1000
 * ! All integers in nums are unique.
 */

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(std::vector<int>& nums)
    {
        const int n = nums.size();
        return build(0, n - 1, nums);
    }

private:
    TreeNode* build(int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return nullptr;

        int maxIndex = -1;
        int maxValue = INT_MIN;
        for (int i = lo; i <= hi; ++i) {
            if (nums[i] > maxValue) {
                maxIndex = i;
                maxValue = nums[i];
            }
        }
        auto* root = new TreeNode(maxValue);
        root->left = build(lo, maxIndex - 1, nums);
        root->right = build(maxIndex + 1, hi, nums);
        return root;
    }
};