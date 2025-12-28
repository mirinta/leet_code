#include <queue>
#include <vector>

/**
 * There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is
 * represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes
 * adjacent to node i, meaning there is an edge from node i to each node in graph[i].
 *
 * A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible
 * path starting from that node leads to a terminal node (or another safe node).
 *
 * Return an array containing all the safe nodes of the graph. The answer should be sorted in
 * ascending order.
 *
 * ! n == graph.length
 * ! 1 <= n <= 10^4
 * ! 0 <= graph[i].length <= n
 * ! 0 <= graph[i][j] <= n - 1
 * ! graph[i] is sorted in a strictly increasing order.
 * ! The graph may contain self-loops.
 * ! The number of edges in the graph will be in the range [1, 4 * 10^4].
 */

class Solution {
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        return approach2(graph);
    }

private:
    // Kahn's algorithm, time O(V+E), space O(V+E)
    std::vector<int> approach2(std::vector<std::vector<int>>& graph)
    {
        // reverse the original graph:
        const int n = graph.size();
        std::vector<std::vector<int>> reversedGraph(n, std::vector<int>());
        std::vector<int> indegrees(n, 0);
        for (int i = 0; i < n; ++i) {
            for (const auto& adj : graph[i]) {
                reversedGraph[adj].push_back(i);
                indegrees[i]++;
            }
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<bool> isSafe(n, false);
        while (!queue.empty()) {
            const int i = queue.front();
            queue.pop();
            isSafe[i] = true;
            for (const auto& adj : reversedGraph[i]) {
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (isSafe[i]) {
                result.push_back(i);
            }
        }
        return result;
    }

    // White = not processed, Gray = being processed, Black = process finished
    enum Color { White, Gray, Black };

    // DFS with colors, time O(V+E), space O(V)
    std::vector<int> approach1(std::vector<std::vector<int>>& graph)
    {
        // node i is a safe node if there's no cycle starting from node i
        const int n = graph.size();
        std::vector<int> result;
        std::vector<int> colors(n, White);
        for (int i = 0; i < n; ++i) {
            // colors can be reused:
            // if we can reach node i from node j,
            // and there's a cycle starting from node i,
            // then there must be a cycle starting from node j
            if (!hasCycle(colors, i, graph)) {
                result.push_back(i);
            }
        }
        return result;
    }

    bool hasCycle(std::vector<int>& colors, int source, const std::vector<std::vector<int>>& graph)
    {
        colors[source] = Gray;
        for (const auto& adj : graph[source]) {
            if (colors[adj] == Gray)
                return true;

            if (colors[adj] == White && hasCycle(colors, adj, graph))
                return true;
        }
        colors[source] = Black;
        return false;
    }
};