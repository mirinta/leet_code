#include <array>

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
 * Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said
 * to be pseudo-palindromic if at least one permutation of the node values in the path is a
 * palindrome.
 *
 * Return the number of pseudo-palindromic paths going from the root node to leaf nodes.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 1 <= Node.val <= 9
 */

class Solution {
public:
    int pseudoPalindromicPaths(TreeNode* root)
    {
        std::array<int, 10> freq{};
        std::fill(freq.begin(), freq.end(), 0);
        int result = 0;
        dfs(result, freq, root);
        return result;
    }

private:
    void dfs(int& result, std::array<int, 10>& freq, TreeNode* node)
    {
        if (!node)
            return;

        freq[node->val]++;
        if (!node->left && !node->right && isValid(freq)) {
            result++;
        }
        dfs(result, freq, node->left);
        dfs(result, freq, node->right);
        freq[node->val]--;
    }

    bool isValid(const std::array<int, 10>& freq)
    {
        int odd = 0;
        for (const auto& val : freq) {
            if (val % 2 != 0) {
                odd++;
            }
            if (odd > 1)
                return false;
        }
        return true;
    }
};