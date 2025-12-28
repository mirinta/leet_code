#include <functional>
#include <vector>

/**
 * You are given two integers, n and threshold, as well as a directed weighted graph of n nodes
 * numbered from 0 to n - 1. The graph is represented by a 2D integer array edges, where edges[i] =
 * [Ai, Bi, Wi] indicates that there is an edge going from node Ai to node Bi with weight Wi.
 *
 * You have to remove some edges from this graph (possibly none), so that it satisfies the following
 * conditions:
 *
 * - Node 0 must be reachable from all other nodes.
 *
 * - The maximum edge weight in the resulting graph is minimized.
 *
 * - Each node has at most threshold outgoing edges.
 *
 * Return the minimum possible value of the maximum edge weight after removing the necessary edges.
 * If it is impossible for all conditions to be satisfied, return -1.
 *
 * ! 2 <= n <= 10^5
 * ! 1 <= threshold <= n - 1
 * ! 1 <= edges.length <= min(10^5, n * (n - 1) / 2).
 * ! edges[i].length == 3
 * ! 0 <= Ai, Bi < n
 * ! Ai != Bi
 * ! 1 <= Wi <= 10^6
 * ! There may be multiple edges between a pair of nodes, but they must have unique weights.
 */

class Solution {
public:
    int minMaxWeight(int n, std::vector<std::vector<int>>& edges, int threshold)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n); // invert
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& e : edges) {
            graph[e[1]].emplace_back(e[0], e[2]);
            min = std::min(min, e[2]);
            max = std::max(max, e[2]);
        }
        int lo = min;
        int hi = max;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, graph)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo > max ? -1 : lo;
    }

private:
    bool isValid(int maxWeight, const std::vector<std::vector<std::pair<int, int>>>& graph)
    {
        // threshold is guaranteed <= n - 1
        const int n = graph.size();
        int count = 0;
        std::vector<bool> visited(n, false);
        std::function<void(int)> dfs = [&](int i) {
            visited[i] = true;
            count++;
            for (const auto& [adj, weight] : graph[i]) {
                if (!visited[adj] && weight <= maxWeight) {
                    dfs(adj);
                }
            }
        };
        dfs(0);
        return count == n;
    }
};