#include <unordered_set>
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
 * Given the roots of two binary search trees, root1 and root2, return true if and only if there is
 * a node in the first tree and a node in the second tree whose values sum up to a given integer
 * target.
 *
 * ! The number of nodes in each tree is in the range [1, 5000].
 * ! -10^9 <= Node.val, target <= 10^9
 */

class Solution {
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target)
    {
        return approach2(root1, root2, target);
    }

private:
    bool search(int target, TreeNode* root)
    {
        if (!root)
            return false;

        if (root->val == target)
            return true;

        if (root->val > target)
            return search(target, root->left);

        return search(target, root->right);
    }

    bool approach2(TreeNode* root1, TreeNode* root2, int target)
    {
        if (!root1)
            return false;

        if (search(target - root1->val, root2))
            return true;

        return twoSumBSTs(root1->left, root2, target) || twoSumBSTs(root1->right, root2, target);
    }

    void traverse(std::unordered_set<int>& nums, TreeNode* root)
    {
        if (!root)
            return;

        nums.emplace(root->val);
        traverse(nums, root->left);
        traverse(nums, root->right);
    }

    bool approach1(TreeNode* root1, TreeNode* root2, int target)
    {
        std::unordered_set<int> nums1;
        std::unordered_set<int> nums2;
        traverse(nums1, root1);
        traverse(nums2, root2);
        for (const auto& val1 : nums1) {
            if (nums2.count(target - val1))
                return true;
        }
        return false;
    }
};
