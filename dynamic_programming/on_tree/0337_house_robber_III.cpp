#include <utility>

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
 * The thief has found himself a new place for this thievery again. There is only one entrance to
 * this area, called "root".
 *
 * Besides the "root", each house has one and only one parent house. After a tour, the smart thief
 * realized that all houses in this place from a binary tree. It will automatically contact the
 * police if two directly-linked houses were broken into on the same night.
 *
 * Given the "root" of the binary tree, return the maximum amount of money the thief can rob without
 * altering the police.
 *
 * ! 0 <= Node.val <= 10^4
 */

class Solution {
public:
    int rob(TreeNode* root)
    {
        if (!root)
            return 0;

        const auto [rootRobbed, rootNotRobbed] = dfs(root);
        return std::max(rootRobbed, rootNotRobbed);
    }

private:
    // return values = <max gain if root node is robbed, max gain if root node is not robbed>
    std::pair<int, int> dfs(TreeNode* root)
    {
        if (!root)
            return {0, 0};

        const auto [leftRobbed, leftNotRobbed] = dfs(root->left);
        const auto [rightRobbed, rightNotRobbed] = dfs(root->right);
        const auto rootRobbed = root->val + leftNotRobbed + rightNotRobbed;
        const auto rootNotRobbed = std::max(leftRobbed, leftNotRobbed) + std::max(rightRobbed, rightNotRobbed);
        return {rootRobbed, rootNotRobbed};
    }
};