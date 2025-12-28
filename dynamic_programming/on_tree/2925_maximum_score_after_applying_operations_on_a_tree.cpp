#include <numeric>
#include <vector>

/**
 * There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are
 * given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is
 * an edge between nodes ai and bi in the tree.
 *
 * You are also given a 0-indexed integer array values of length n, where values[i] is the value
 * associated with the ith node.
 *
 * You start with a score of 0. In one operation, you can:
 *
 * - Pick any node i.
 *
 * - Add values[i] to your score.
 *
 * - Set values[i] to 0.
 *
 * A tree is healthy if the sum of values on the path from the root to any leaf node is different
 * than zero.
 *
 * Return the maximum score you can obtain after performing these operations on the tree any number
 * of times so that it remains healthy.
 *
 * ! 2 <= n <= 2 * 10^4
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! values.length == n
 * ! 1 <= values[i] <= 10^9
 * ! The input is generated such that edges represents a valid tree.
 */

class Solution {
public:
    long long maximumScoreAfterOperations(std::vector<std::vector<int>>& edges, std::vector<int>& values)
    {
        const int n = values.size();
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        const long long total = std::accumulate(values.begin(), values.end(), 0LL);
        return total - dfs(0, -1, values, graph);
    }

private:
    // return the min sum of the given tree
    // each node can be ignored or picked, the sum must be greater than 0
    long long dfs(int root, int parent, const std::vector<int>& values, const std::vector<std::vector<int>>& graph)
    {
        long long sumOfSubtrees = 0;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            sumOfSubtrees += dfs(child, root, values, graph);
        }
        if (sumOfSubtrees == 0)
            return values[root];

        return std::min<long long>(values[root], sumOfSubtrees);
    }
};