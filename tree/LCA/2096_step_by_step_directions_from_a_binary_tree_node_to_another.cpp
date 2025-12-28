#include <string>

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
 * You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from
 * 1 to n. You are also given an integer startValue representing the value of the start node s, and
 * a different integer destValue representing the value of the destination node t.
 *
 * Find the shortest path starting from node s and ending at node t. Generate step-by-step
 * directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'.
 * Each letter indicates a specific direction:
 *
 * - 'L' means to go from a node to its left child node.
 *
 * - 'R' means to go from a node to its right child node.
 *
 * - 'U' means to go from a node to its parent node.
 *
 * Return the step-by-step directions of the shortest path from node s to node t.
 *
 * ! The number of nodes in the tree is n.
 * ! 2 <= n <= 10^5
 * ! 1 <= Node.val <= n
 * ! All the values in the tree are unique.
 * ! 1 <= startValue, destValue <= n
 * ! startValue != destValue
 */

class Solution {
public:
    std::string getDirections(TreeNode* root, int startValue, int destValue)
    {
        if (!root)
            return {};

        dfs(root, startValue, destValue);
        std::string result;
        backtrack(result, lca, startValue);
        std::fill(result.begin(), result.end(), 'U');
        backtrack(result, lca, destValue);
        return result;
    }

private:
    TreeNode* lca;

    int dfs(TreeNode* root, int p, int q)
    {
        if (!root)
            return 0;

        int count = root->val == p || root->val == q;
        count += dfs(root->left, p, q);
        count += dfs(root->right, p, q);
        if (count == 2 && !lca) {
            lca = root;
        }
        return count;
    }

    bool backtrack(std::string& path, TreeNode* root, int target)
    {
        if (!root)
            return false;

        if (root->val == target)
            return true;

        path.push_back('L');
        if (backtrack(path, root->left, target))
            return true;

        path.back() = 'R';
        if (backtrack(path, root->right, target))
            return true;

        path.pop_back();
        return false;
    }
};
