#include <queue>
#include <unordered_set>
#include <vector>

/**
 * You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an
 * array graph where graph[i] is a list of all the nodes connected with node i by an edge.
 *
 * Return the length of the shortest path that visits every node. You may start and stop at any
 * node, you may revisit nodes multiple times, and you may reuse edges.
 *
 * ! n == graph.length
 * ! 1 <= n <= 12
 * ! 0 <= graph[i].length < n
 * ! graph[i] does not contain i.
 * ! If graph[a] contains b, then graph[b] contains a.
 * ! The input graph is always connected.
 */

class Solution {
public:
    int shortestPathLength(std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        const int target = (1 << n) - 1;
        std::vector<std::unordered_set<int>> visited(n);
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < n; ++i) {
            queue.emplace(i, 1 << i);
            visited[i].insert(1 << i);
        }
        int result = -1;
        while (!queue.empty()) {
            result++;
            for (int k = queue.size(); k > 0; --k) {
                const auto [v, state] = queue.front();
                queue.pop();
                if (state == target)
                    return result;

                for (const auto& adj : graph[v]) {
                    const int newState = state | (1 << adj);
                    if (visited[adj].count(newState))
                        continue;

                    visited[adj].insert(newState);
                    queue.emplace(adj, newState);
                }
            }
        }
        return result;
    }
};
