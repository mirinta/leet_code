#include <queue>
#include <string>
#include <vector>

/**
 * There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.
 *
 * You are given a string colors where colors[i] is a lowercase English letter representing the
 * color of the ith node in this graph (0-indexed). You are also given a 2D array edges where
 * edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.
 *
 * A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a
 * directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of
 * nodes that are colored the most frequently occurring color along that path.
 *
 * Return the largest color value of any valid path in the given graph, or -1 if the graph contains
 * a cycle.
 *
 * ! n == colors.length
 * ! m == edges.length
 * ! 1 <= n <= 10^5
 * ! 0 <= m <= 10^5
 * ! colors consists of lowercase English letters.
 * ! 0 <= aj, bj < n
 */

class Solution {
public:
    // topological sorting (Kahn's algo) + DP, time O(V+E), space (V+E)
    int largestPathValue(std::string colors, std::vector<std::vector<int>>& edges)
    {
        const int n = colors.size();
        std::vector<std::vector<int>> graph(n);
        std::vector<int> indegrees(n, 0);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            indegrees[edge[1]]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        // dp[i][j] = max num of vertices with color j of a path starting from vertex i
        std::vector<std::vector<int>> dp(n, std::vector<int>(26, 0));
        int numOfVertices = 0; // numOfVertices != n means there's a cycle in the graph
        int result = 0;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            numOfVertices++;
            result = std::max(result, ++dp[v][colors[v] - 'a']);
            for (const auto& adj : graph[v]) {
                for (int i = 0; i < 26; ++i) {
                    dp[adj][i] = std::max(dp[adj][i], dp[v][i]);
                }
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        return numOfVertices == n ? result : -1;
    }
};