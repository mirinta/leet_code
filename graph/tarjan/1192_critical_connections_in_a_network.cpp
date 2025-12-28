#include <vector>

/**
 * There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections
 * forming a network where connections[i] = [ai, bi] represents a connection between servers ai and
 * bi. Any server can reach other servers directly or indirectly through the network.
 *
 * A critical connection is a connection that, if removed, will make some servers unable to reach
 * some other server.
 *
 * Return all critical connections in the network in any order.
 *
 * ! 2 <= n <= 10^5
 * ! n - 1 <= connections.length <= 10^5
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 * ! There are no repeated connections.
 */

class Solution {
public:
    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : connections) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        time = 0;
        dfn = std::vector<int>(n, -1);
        low = std::vector<int>(n, -1);
        result.clear();
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                dfs(i, -1, graph);
            }
        }
        return result;
    }

private:
    int time;
    std::vector<int> dfn;
    std::vector<int> low;
    std::vector<std::vector<int>> result;

    void dfs(int current, int parent, const std::vector<std::vector<int>>& graph)
    {
        dfn[current] = low[current] = ++time;
        for (const auto& next : graph[current]) {
            if (next == parent)
                continue;

            if (dfn[next] == -1) {
                dfs(next, current, graph);
                if (low[next] > dfn[current]) {
                    result.push_back({current, next});
                }
                low[current] = std::min(low[current], low[next]);
            } else {
                low[current] = std::min(low[current], dfn[next]);
            }
        }
    }
};
