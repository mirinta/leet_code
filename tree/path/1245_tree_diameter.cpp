#include <vector>

/**
 * The diameter of a tree is the number of edges in the longest path in that tree.
 *
 * There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges
 * where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge
 * between nodes ai and bi in the tree.
 *
 * Return the diameter of the tree.
 *
 * ! n == edges.length + 1
 * ! 1 <= n <= 10^4
 * ! 0 <= ai, bi < n
 * ! ai != bi
 */

class Solution {
public:
    int treeDiameter(std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int result = 0;
        dfs(result, 0, -1, graph);
        return result;
    }

private:
    // return the max depth (num of edges) of the given tree
    int dfs(int& result, int root, int parent, const std::vector<std::vector<int>>& graph)
    {
        int maxDepth = 0;
        int secondMaxDepth = 0;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            const int depth = dfs(result, child, root, graph) + 1;
            if (depth > maxDepth) {
                std::swap(maxDepth, secondMaxDepth);
                maxDepth = depth;
            } else if (depth > secondMaxDepth) {
                secondMaxDepth = depth;
            }
        }
        result = std::max(result, maxDepth + secondMaxDepth);
        return maxDepth;
    }
};