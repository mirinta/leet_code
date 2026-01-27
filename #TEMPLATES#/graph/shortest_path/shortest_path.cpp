#include "definition.h"

/**
 * @brief Calculate the weights of shortest paths for all pairs of vertices using the Floyd-Warshall
 * algorithm.
 *
 * @note Negative edge weights are allowed, but the given graph must not have negative cycles.
 *
 * @note The returned matrix is 0-indexed.
 *
 * @note matrix[i][j] = LLONG_MAX indicates that it is not reachable from i to j.
 *
 * @note Time Complexity = O(V^3), Space Complexity = O(V^2), where V is the number of vertices.
 */
std::vector<std::vector<long long>> floydWarshall(const Graph& graph)
{
    const int n = graph.size();
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (const auto& [j, weight] : graph[i]) {
            dist[i][j] = std::min(dist[i][j], weight);
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == LLONG_MAX)
                continue;

            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == LLONG_MAX)
                    continue;

                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

/**
 * @brief Calculate the weight of the shortest path from src to dst using the Bellman-Ford
 * algorithm.
 *
 * @note Negative edge weights are allowed, but the given graph must not have negative cycles.
 *
 * @note Return LLONG_MAX if it is not reachable from src to dst.
 *
 * @note Time Complexity = O(EV), Space Complexity = O(V), where E and V are the number of vertices
 * and edges, respectively.
 */
long long bellmanFord(int src, int dst, int V, const Edges& edges)
{
    std::vector<long long> dp(V, LLONG_MAX);
    dp[src] = 0;
    for (int i = 1; i <= V - 1; ++i) {
        bool updated = false;
        for (const auto& [from, to, weight] : edges) {
            if (dp[from] != LLONG_MAX && dp[from] + weight < dp[to]) {
                updated = true;
                dp[to] = dp[from] + weight;
            }
        }
        if (!updated)
            break;
    }
    return dp[dst];
}
