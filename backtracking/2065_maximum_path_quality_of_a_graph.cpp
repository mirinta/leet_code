#include <functional>
#include <vector>

/**
 * There is an undirected graph with n nodes numbered from 0 to n - 1 (inclusive). You are given a
 * 0-indexed integer array values where values[i] is the value of the ith node. You are also given a
 * 0-indexed 2D integer array edges, where each edges[j] = [uj, vj, timej] indicates that there is
 * an undirected edge between the nodes uj and vj, and it takes timej seconds to travel between the
 * two nodes. Finally, you are given an integer maxTime.
 *
 * A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most
 * maxTime seconds to complete. You may visit the same node multiple times. The quality of a valid
 * path is the sum of the values of the unique nodes visited in the path (each node's value is added
 * at most once to the sum).
 *
 * Return the maximum quality of a valid path.
 *
 * Note: There are at most four edges connected to each node
 *
 * ! n == values.length
 * ! 1 <= n <= 1000
 * ! 0 <= values[i] <= 10^8
 * ! 0 <= edges.length <= 2000
 * ! edges[j].length == 3
 * ! 0 <= uj < vj <= n - 1
 * ! 10 <= timej, maxTime <= 100
 * ! All the pairs [uj, vj] are unique.
 * ! There are at most four edges connected to each node.
 * ! The graph may not be connected.
 */

class Solution {
public:
    int maximalPathQuality(std::vector<int>& values, std::vector<std::vector<int>>& edges, int maxTime)
    {
        const int n = values.size();
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        std::vector<int> visited(n, 0);
        visited[0] = 1;
        int result = 0;
        std::function<void(int, int, int)> backtrack = [&](int v, int time, int score) {
            if (v == 0) {
                result = std::max(result, score);
            }
            for (const auto& [adj, t] : graph[v]) {
                if (t + time > maxTime)
                    continue;

                visited[adj]++;
                backtrack(adj, time + t, score + (visited[adj] == 1) * values[adj]);
                visited[adj]--;
            }
        };
        backtrack(0, 0, values[0]);
        return result;
    }
};