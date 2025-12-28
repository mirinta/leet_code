#include <queue>
#include <vector>

/**
 * This is an undirected graph with "n" nodes, where each node is numbered between 0 and n - 1. You
 * are given a 2D array "graph", where graph[u] is an array of nodes that node "u" is adjacent to.
 * More formally, for each "v" in graph[u], there is an undirected edge between node "u" and node
 * "v". The graph has the following properties:
 *
 * - Thee are no self-edges (graph[u] does not contain u).
 *
 * - There are no parallel edges (graph[u] does not contain duplicate values).
 *
 * - If v is in graph[u], then u is in graph[v] (the graph is undirected).
 *
 * - The graph may not be connected, meaning there may be two nodes u and v such that there is no
 * path between them.
 *
 * A graph is bipartite if the nodes can be partitioned into two independent sets "A" and "B" such
 * that every edge in the graph connects a node in set "A" and a node in set "B".
 *
 * Return true if and only if it is bipartite.
 *
 * ! graph.length == n
 * ! 1 <= n <= 100
 * ! 0 <= graph[u].length < n
 * ! 0 <= graph[u][i] <= n - 1
 * ! graph[u] does not contain u.
 * ! All the values of graph[u] are unique.
 * ! If graph[u] contains v, then graph[v] contains u.
 */

class Solution {
public:
    bool isBipartite(const std::vector<std::vector<int>>& graph)
    {
        return approach1(graph);
    }

private:
    // BFS, time O(V+E), space O(V+E)
    int approach2(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<int> colors(n, 0); // 0 for not visited, -1 for blue, 1 for red
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (colors[i] != 0)
                continue;

            queue.push(i);
            colors[i] = 1;
            while (!queue.empty()) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& adj : graph[v]) {
                    if (colors[adj] == 0) {
                        colors[adj] = -colors[v];
                        queue.push(adj);
                    } else if (colors[adj] == colors[v])
                        return false;
                }
            }
        }
        return true;
    }

    // DFS, time O(V+E), space O(V+E)
    int approach1(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<int> colors(n, 0); // 0 for not visited, -1 for blue, 1 for red
        for (int i = 0; i < n; ++i) {
            if (colors[i] != 0)
                continue;

            colors[i] = 1; // -1 is also correct
            if (!dfs(colors, i, graph))
                return false;
        }
        return true;
    }

    bool dfs(std::vector<int>& colors, int v, const std::vector<std::vector<int>>& graph)
    {
        for (const auto& adj : graph[v]) {
            if (colors[adj] == 0) {
                colors[adj] = -colors[v];
                if (!dfs(colors, adj, graph))
                    return false;

            } else if (colors[adj] == colors[v])
                return false;
        }
        return true;
    }
};
