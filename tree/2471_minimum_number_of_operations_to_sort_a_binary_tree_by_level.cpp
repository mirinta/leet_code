#include <algorithm>
#include <queue>
#include <unordered_map>
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
 * You are given the root of a binary tree with unique values.
 *
 * In one operation, you can choose any two nodes at the same level and swap their values.
 *
 * Return the minimum number of operations needed to make the values at each level sorted in a
 * strictly increasing order.
 *
 * The level of a node is the number of edges along the path between it and the root node.
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 * ! All the values of the tree are unique.
 */

class Solution {
public:
    int minimumOperations(TreeNode* root)
    {
        if (!root)
            return 0;

        std::queue<TreeNode*> queue;
        queue.push(root);
        std::vector<int> values;
        int result = 0;
        while (!queue.empty()) {
            const int n = queue.size();
            values.resize(n);
            for (int i = 0; i < n; ++i) {
                auto* node = queue.front();
                queue.pop();
                values[i] = node->val;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result += helper(values);
        }
        return result;
    }

private:
    int helper(std::vector<int>& values)
    {
        const int n = values.size();
        auto sorted = values;
        std::sort(sorted.begin(), sorted.end());
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[sorted[i]] = i;
        }
        int count = 0;
        for (int i = 0; i < n; ++i) {
            while (map[values[i]] != i) {
                std::swap(values[i], values[map[values[i]]]);
                count++;
            }
        }
        return count;
    }
};