#include <queue>
#include <vector>

/**
 * You are given an integer n, the number of nodes in a directed graph where the nodes are labeled
 * from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and
 * parallel edges.
 *
 * You are given two arrays redEdges and blueEdges where:
 *
 * - redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in
 * the graph, and
 *
 * - blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in
 * the graph.
 *
 * Return an array answer of length n, where each answer[x] is the length of the shortest path from
 * node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does
 * not exist.
 *
 * ! 1 <= n <= 100
 * ! 0 <= redEdges.length, blueEdges.length <= 400
 * ! redEdges[i].length == blueEdges[j].length == 2
 * ! 0 <= ai, bi, uj, vj < n
 */

class Solution {
public:
    // BFS, time (V+E), space O(V+E)
    std::vector<int> shortestAlternatingPaths(int n,
                                              std::vector<std::vector<int>>& redEdges,
                                              std::vector<std::vector<int>>& blueEdges)
    {
        constexpr int kRed = 0;
        constexpr int kBlue = 1;
        std::vector<std::vector<std::vector<int>>> graph(n, std::vector<std::vector<int>>(2));
        for (const auto& edge : redEdges) {
            graph[edge[0]][kRed].push_back(edge[1]);
        }
        for (const auto& edge : blueEdges) {
            graph[edge[0]][kBlue].push_back(edge[1]);
        }
        std::queue<std::pair<int, int>> queue; // <vertex, color>
        queue.emplace(0, kRed);
        queue.emplace(0, kBlue);
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(2, false));
        visited[0][kRed] = true;
        ;
        visited[0][kBlue] = true;
        ;
        std::vector<int> result(n, -1);
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [v, color] = queue.front();
                queue.pop();
                if (result[v] == -1) {
                    result[v] = steps;
                }
                const int requiredColor = 1 - color;
                for (const auto& adj : graph[v][requiredColor]) {
                    if (visited[adj][requiredColor])
                        continue;

                    visited[adj][requiredColor] = true;
                    queue.emplace(adj, requiredColor);
                }
            }
            steps++;
        }
        return result;
    }
};
