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
 * You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1
 * to n. You are also given an array queries of size m.
 *
 * You have to perform m independent queries on the tree where in the ith query you do the
 * following:
 *
 * - Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed
 * that queries[i] will not be equal to the value of the root.
 *
 * Return an array answer of size m where answer[i] is the height of the tree after performing the
 * ith query.
 *
 * Note:
 *
 * - The queries are independent, so the tree returns to its initial state after each query.
 *
 * - The height of a tree is the number of edges in the longest simple path from the root to some
 * node in the tree.
 *
 * ! The number of nodes in the tree is n.
 * ! 2 <= n <= 10^5
 * ! 1 <= Node.val <= n
 * ! All the values in the tree are unique.
 * ! m == queries.length
 * ! 1 <= m <= min(n, 10^4)
 * ! 1 <= queries[i] <= n
 * ! queries[i] != root.val
 */

class Solution {
public:
    std::vector<int> treeQueries(TreeNode* root, std::vector<int>& queries)
    {
        dfs(root, 0);
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& v : queries) {
            const auto& [v1, v2] = map[depth[v]];
            if (v != v1) {
                result.push_back(depth[v1] + height[v1]);
            } else if (v2 != -1) {
                result.push_back(depth[v2] + height[v2]);
            } else {
                result.push_back(depth[v] - 1);
            }
        }
        return result;
    }

private:
    std::unordered_map<int, int> depth;
    std::unordered_map<int, int> height;
    // map[i] = {v1, v2}, v1 and v2 are the max height and the second max height subtree of level i
    std::unordered_map<int, std::pair<int, int>> map;

    int dfs(TreeNode* root, int level)
    {
        if (!root)
            return -1;

        if (!map.count(level)) {
            map[level] = {-1, -1};
        }
        const int v = root->val;
        depth[v] = level;
        height[v] = 1 + std::max(dfs(root->left, level + 1), dfs(root->right, level + 1));
        auto& [v1, v2] = map[level];
        if (v1 == -1) {
            v1 = v;
        } else if (height[v] > height[v1]) {
            v2 = v1;
            v1 = v;
        } else if (v2 == -1 || height[v] > height[v2]) {
            v2 = v;
        }
        return height[root->val];
    }
};
