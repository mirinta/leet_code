#include <algorithm>
#include <queue>
#include <vector>

/**
 * Given an undirected tree consisting of n vertices numbered from 1 to n. A frog starts jumping
 * from vertex 1. In one second, the frog jumps from its current vertex to another unvisited vertex
 * if they are directly connected. The frog can not jump back to a visited vertex. In case the frog
 * can jump to several vertices, it jumps randomly to one of them with the same probability.
 * Otherwise, when the frog can not jump to any unvisited vertex, it jumps forever on the same
 * vertex.
 *
 * The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means
 * that exists an edge connecting the vertices ai and bi.
 *
 * Return the probability that after t seconds the frog is on the vertex target. Answers within 10-5
 * of the actual answer will be accepted.
 *
 * ! 1 <= n <= 100
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 1 <= ai, bi <= n
 * ! 1 <= t <= 50
 * ! 1 <= target <= n
 */

class Solution {
public:
    double frogPosition(int n, std::vector<std::vector<int>>& edges, int t, int target)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            const auto v = edge[0] - 1; // to 0-indexed
            const auto w = edge[1] - 1; // to 0-indexed
            graph[v].push_back(w);
            graph[w].push_back(v);
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        std::vector<double> prob(n, 0);
        prob[0] = 1.0;
        std::queue<int> queue;
        queue.push(0);
        while (!queue.empty() && t > 0) {
            t--;
            for (int i = queue.size(); i > 0; --i) {
                const auto v = queue.front();
                queue.pop();
                const int count =
                    std::count_if(graph[v].begin(), graph[v].end(), [&visited](const int w) { return !visited[w]; });
                for (const auto& w : graph[v]) {
                    if (visited[w])
                        continue;

                    prob[w] = prob[v] / count;
                    visited[w] = true;
                    queue.push(w);
                }
                if (count > 0) {
                    // if there exists unvisited vertices,
                    // the frog can't stay at v
                    prob[v] = 0;
                }
            }
        }
        return prob[target - 1]; // target is 1-indexed
    }
};
