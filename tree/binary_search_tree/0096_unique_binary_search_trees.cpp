#include <unordered_map>

/**
 Definition for a binary tree node.
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
 * Given an integer "n", return the number of structurally unique BST's which has exactly "n" nodes
 * of unique values from "1" to "n".
 */

/**
 * vals = 1, 2, 3, 4, 5
 * If we use 3 as the root node,
 * - values in its left subtree = 1, 2, there are 2 ways to build the left subtree
 * - values in its right subtree = 4, 5, there are 2 ways to build the right subtree
 * - therefore, the number of trees that use 3 as the root node is 2 x 2 = 4
 *
 * https://mp.weixin.qq.com/s/kcwz2lyRxxOsC3n11qdVSw
 */

class Solution {
public:
    int numTrees(int n)
    {
        if (n <= 1)
            return 1;

        if (map.count(n))
            return map[n];

        int result = 0;
        for (int i = 1; i <= n; ++i) {
            result += numTrees(i - 1) * numTrees(n - i);
        }
        map[n] = result;
        return result;
    }

private:
    std::unordered_map<int, int> map; // store results to avoid repeated computation
};