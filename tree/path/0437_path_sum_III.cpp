#include <unordered_map>

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
 * Given the root of a binary tree and an integer targetSum, return the number of paths where the
 * sum of the values along the path equals targetSum.
 *
 * The path does not need to start or end at the root or a leaf, but it must go downwards (i.e.,
 * traveling only from parent nodes to child nodes).
 *
 * ! The number of nodes in the tree is in the range [0, 1000].
 * ! -10^9 <= Node.val <= 10^9
 * ! -1000 <= targetSum <= 1000
 */

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        if (!root)
            return 0;

        std::unordered_map<long, int> map; // prefix sum to frequency
        int result = 0;
        backtrack(result, map, root, 0, targetSum);
        return result;
    }

private:
    void backtrack(int& result, std::unordered_map<long, int>& map, TreeNode* node, long currentPrefix, long targetSum)
    {
        if (!node)
            return;

        currentPrefix += node->val;
        if (currentPrefix == targetSum) {
            result++;
        }
        // START X ... X X X X ... X X
        // |<-prefix'->| |<--target->|
        // |<---------prefix-------->|
        if (const long prevPrefix = currentPrefix - targetSum; map.count(prevPrefix)) {
            result += map[prevPrefix];
        }
        map[currentPrefix]++;
        backtrack(result, map, node->left, currentPrefix, targetSum);
        backtrack(result, map, node->right, currentPrefix, targetSum);
        map[currentPrefix]--;
    }
};