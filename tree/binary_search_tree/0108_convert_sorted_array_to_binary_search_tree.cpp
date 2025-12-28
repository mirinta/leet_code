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
 * Given an integer array "nums" where the elements are sorted in ascending order, convert it to a
 * height-balanced binary search tree.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every
 * node never differs by more than one.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! nums is sorted in a strictly increasing order.
 */

class Solution {
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums)
    {
        const int n = nums.size();
        return build(0, n - 1, nums);
    }

private:
    TreeNode* build(int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return nullptr;

        // if nums[X] is the root node of a balanced BST, then
        // nums[lo:X) < nums[X], nums(X:hi] > nums[X]
        // and |(X-lo) - (hi-X)| = |2*X - (hi+lo)| <= 1
        const int x = lo + (hi - lo) / 2;
        auto* root = new TreeNode(nums[x]);
        root->left = build(lo, x - 1, nums);
        root->right = build(x + 1, hi, nums);
        return root;
    }
};
