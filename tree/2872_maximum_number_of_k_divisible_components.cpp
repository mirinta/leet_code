#include <vector>

/**
 * There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and
 * a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an
 * edge between nodes ai and bi in the tree.
 *
 * You are also given a 0-indexed integer array values of length n, where values[i] is the value
 * associated with the ith node, and an integer k.
 *
 * A valid split of the tree is obtained by removing any set of edges, possibly empty, from the tree
 * such that the resulting components all have values that are divisible by k, where the value of a
 * connected component is the sum of the values of its nodes.
 *
 * Return the maximum number of components in any valid split.
 *
 * ! 1 <= n <= 3 * 10^4
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! values.length == n
 * ! 0 <= values[i] <= 10^9
 * ! 1 <= k <= 10^9
 * ! Sum of values is divisible by k.
 * ! The input is generated such that edges represents a valid tree.
 */

class Solution {
public:
    int maxKDivisibleComponents(int n, std::vector<std::vector<int>>& edges, std::vector<int>& values, int k)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        int result = 0;
        dfs(result, 0, -1, k, values, graph);
        return result;
    }

private:
    int dfs(int& result,
            int node,
            int parent,
            int k,
            const std::vector<int>& values,
            const std::vector<std::vector<int>>& graph)
    {
        int sum = values[node] % k;
        for (const auto& next : graph[node]) {
            if (next == parent)
                continue;

            sum = (sum + dfs(result, next, node, k, values, graph)) % k;
        }
        result += sum == 0;
        return sum;
    }
};