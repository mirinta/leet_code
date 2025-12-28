#include <vector>

/**
 * You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n
 * - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between
 * vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
 *
 * Two servers a and b are connectable through a server c if:
 *
 * - a < b, a != c and b != c.
 *
 * - The distance from c to a is divisible by signalSpeed.
 *
 * - The distance from c to b is divisible by signalSpeed.
 *
 * - The path from c to b and the path from c to a do not share any edges.
 *
 * Return an integer array count of length n where count[i] is the number of server pairs that are
 * connectable through the server i.
 *
 * ! 2 <= n <= 1000
 * ! edges.length == n - 1
 * ! edges[i].length == 3
 * ! 0 <= ai, bi < n
 * ! edges[i] = [ai, bi, weighti]
 * ! 1 <= weighti <= 10^6
 * ! 1 <= signalSpeed <= 10^6
 * ! The input is generated such that edges represents a valid tree.
 */

class Solution {
public:
    std::vector<int> countPairsOfConnectableServers(std::vector<std::vector<int>>& edges, int signalSpeed)
    {
        const int n = edges.size() + 1;
        Graph graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        std::vector<int> result(n);
        for (int root = 0; root < n; ++root) {
            result[root] = solve(root, signalSpeed, graph);
        }
        return result;
    }

private:
    using Graph = std::vector<std::vector<std::pair<int, int>>>;

    int solve(int root, int signalSpeed, const Graph& graph)
    {
        int presum = 0;
        int result = 0;
        for (const auto& [v, weight] : graph[root]) {
            const int count = dfs(v, root, weight, signalSpeed, graph);
            result += presum * count;
            presum += count;
        }
        return result;
    }

    int dfs(int root, int parent, int total, int signalSpeed, const Graph& graph)
    {
        int result = total % signalSpeed == 0;
        for (const auto& [v, weight] : graph[root]) {
            if (v == parent)
                continue;

            result += dfs(v, root, total + weight, signalSpeed, graph);
        }
        return result;
    }
};