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
 * You are given the root of a binary tree and an integer distance. A pair of two different leaf
 * nodes of a binary tree is said to be good if the length of the shortest path between them is less
 * than or equal to distance.
 *
 * Return the number of good leaf node pairs in the tree.
 *
 * ! The number of nodes in the tree is in the range [1, 2^10].
 * ! 1 <= Node.val <= 100
 * ! 1 <= distance <= 10
 */

class Solution {
public:
    int countPairs(TreeNode* root, int distance)
    {
        int result = 0;
        dfs(result, root, distance);
        return result;
    }

private:
    // return the distances between each leaf node and the root node
    std::vector<int> dfs(int& result, TreeNode* root, int distance)
    {
        if (!root)
            return {};

        if (!root->left && !root->right)
            return {1};

        const auto left = dfs(result, root->left, distance);
        const auto right = dfs(result, root->right, distance);
        for (const auto& d1 : left) {
            for (const auto& d2 : right) {
                if (d1 + d2 <= distance) {
                    result++;
                }
            }
        }
        std::vector<int> distances;
        distances.reserve(left.size() + right.size());
        for (const auto& d1 : left) {
            distances.push_back(d1 + 1);
        }
        for (const auto& d2 : right) {
            distances.push_back(d2 + 1);
        }
        return distances;
    }
};