#include <functional>
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
 * Given the "root" of a binary tree, determine if it is a valid binary search tree.
 *
 * A valid BST is defined as follows:
 *
 * - The left subtree of a node contains only nodes with keys less than the node's key.
 *
 * - The right subtree of a node contains only nodes with keys greater than the node's key.
 *
 * - Both the left and right subtrees must also be binary search trees.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! -2^31 <= Node.val <= 2^31 - 1
 */

class Solution {
public:
    bool isValidBST(TreeNode* root)
    {
        return approach3(root);
    }

private:
    // post traversal
    bool approach3(TreeNode* root)
    {
        using LL = long long;
        using Pair = std::pair<LL, LL>;
        std::function<Pair(TreeNode*)> dfs = [&dfs](TreeNode* root) {
            if (!root)
                return std::make_pair(LLONG_MAX, LLONG_MIN);

            const auto [leftMin, leftMax] = dfs(root->left);
            const auto [rightMin, rightMax] = dfs(root->right);
            // we want leftMax < root.val < rightMin
            if (leftMax >= root->val || rightMin <= root->val)
                return std::make_pair(LLONG_MIN, LLONG_MAX); // invalid status

            return std::make_pair(std::min<LL>(leftMin, root->val), std::max<LL>(rightMax, root->val));
        };
        return dfs(root).first != LLONG_MIN;
    }

    // preorder traversal
    bool approach2(TreeNode* root)
    {
        using LL = long long;
        std::function<bool(TreeNode*, LL, LL)> dfs = [&dfs](TreeNode* root, LL min, LL max) {
            if (!root)
                return true;

            if (root->val <= min || root->val >= max)
                return false;

            return dfs(root->left, min, root->val) && dfs(root->right, root->val, max);
        };
        return dfs(root, LLONG_MIN, LLONG_MAX);
    }

    // inorder traversal
    bool approach1(TreeNode* root)
    {
        long long prev = LLONG_MIN;
        std::function<bool(TreeNode*)> dfs = [&prev, &dfs](TreeNode* root) {
            if (!root)
                return true;

            if (!dfs(root->left))
                return false;

            if (root->val <= prev)
                return false;

            prev = root->val;
            return dfs(root->right);
        };
        return dfs(root);
    }
};
