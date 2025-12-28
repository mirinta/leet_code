#include <algorithm>
#include <vector>

/**
 * You are given a positive integer n representing the number of nodes of a Directed Acyclic Graph
 * (DAG). The nodes are numbered from 0 to n - 1 (inclusive).
 *
 * You are also given a 2D integer array edges, where edges[i] = [fromi, toi] denotes that there is
 * a unidirectional edge from fromi to toi in the graph.
 *
 * Return a list answer, where answer[i] is the list of ancestors of the ith node, sorted in
 * ascending order.
 *
 * A node u is an ancestor of another node v if u can reach v via a set of edges.
 *
 * ! 1 <= n <= 1000
 * ! 0 <= edges.length <= min(2000, n * (n - 1) / 2)
 * ! edges[i].length == 2
 * ! 0 <= fromi, toi <= n - 1
 * ! fromi != toi
 * ! There are no duplicate edges.
 * ! The graph is directed and acyclic.
 */

class Solution {
public:
    std::vector<std::vector<int>> getAncestors(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> reversedGraph(n);
        for (const auto& edge : edges) {
            reversedGraph[edge[1]].push_back(edge[0]);
        }
        std::vector<std::vector<int>> result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            std::vector<int> ancestors;
            std::vector<bool> visited(n);
            dfs(visited, ancestors, i, reversedGraph);
            ancestors.erase(ancestors.begin());
            std::sort(ancestors.begin(), ancestors.end());
            result.push_back(std::move(ancestors));
        }
        return result;
    }

private:
    void dfs(std::vector<bool>& visited, std::vector<int>& path, int v, const std::vector<std::vector<int>>& graph)
    {
        visited[v] = true;
        path.push_back(v);
        for (const auto& w : graph[v]) {
            if (visited[w])
                continue;

            dfs(visited, path, w, graph);
        }
    }
};