#include <vector>

/**
 * There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
 *
 * You are given a 0-indexed integer array nums of length n where nums[i] represents the value of
 * the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai,
 * bi] indicates that there is an edge between nodes ai and bi in the tree.
 *
 * Remove two distinct edges of the tree to form three connected components. For a pair of removed
 * edges, the following steps are defined:
 *
 * 1. Get the XOR of all the values of the nodes for each of the three components respectively.
 *
 * 2. The difference between the largest XOR value and the smallest XOR value is the score of the
 * pair.
 *
 * - For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The
 * three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and
 * the smallest XOR value is 3. The score is then 8 - 3 = 5.
 *
 * Return the minimum score of any possible pair of edge removals on the given tree.
 *
 * ! n == nums.length
 * ! 3 <= n <= 1000
 * ! 1 <= nums[i] <= 108
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! edges represents a valid tree.
 */

class Solution
{
public:
    int minimumScore(std::vector<int>& nums, std::vector<std::vector<int>>& edges)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        int result = INT_MAX;
        for (const auto& e : edges) {
            // the root of each subtree is determined when e is deleted
            const int root1 = e[0];
            const int root2 = e[1];
            std::vector<std::pair<int, int>> XOR1; // <xor, id>
            const int total1 = dfs(XOR1, root1, -1, root2, nums, graph);
            std::vector<std::pair<int, int>> XOR2; // <xor, id>
            const int total2 = dfs(XOR2, root2, -1, root1, nums, graph);
            helper(result, XOR1, root1, total1, total2); // delete a subtree from root1
            helper(result, XOR2, root2, total2, total1); // delete a subtree from root2
        }
        return result;
    }

private:
    int dfs(std::vector<std::pair<int, int>>& XOR, int node, int parent, int notReachable,
            const std::vector<int>& nums, const std::vector<std::vector<int>>& graph)
    {
        int total = nums[node];
        for (const auto& child : graph[node]) {
            if (child == parent || child == notReachable)
                continue;

            total ^= dfs(XOR, child, node, notReachable, nums, graph);
        }
        XOR.emplace_back(total, node);
        return total;
    }

    void helper(int& result, const std::vector<std::pair<int, int>>& XOR, int root, int total,
                int otherTotal)
    {
        for (const auto& [val, id] : XOR) {
            if (id == root)
                continue;

            const int min = std::min({val, total ^ val, otherTotal});
            const int max = std::max({val, total ^ val, otherTotal});
            result = std::min(result, max - min);
        }
    }
};