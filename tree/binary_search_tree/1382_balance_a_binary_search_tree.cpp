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
 * Given the root of a binary search tree, return a balanced binary search tree with the same node
 * values. If there is more than one answer, return any of them.
 *
 * A binary search tree is balanced if the depth of the two subtrees of every node never differs by
 * more than 1.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 1 <= Node.val <= 10^5
 */

class Solution {
public:
    TreeNode* balanceBST(TreeNode* root)
    {
        std::vector<int> nums;
        traverse(nums, root);
        return build(0, nums.size() - 1, nums);
    }

private:
    void traverse(std::vector<int>& nums, TreeNode* root)
    {
        if (!root)
            return;

        traverse(nums, root->left);
        nums.push_back(root->val);
        traverse(nums, root->right);
    }

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