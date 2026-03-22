#include <vector>

/**
 * There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph would form a tree if its edges were
 * bi-directional.
 *
 * You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi] represents a directed edge going
 * from node ui to node vi.
 *
 * An edge reversal changes the direction of an edge, i.e., a directed edge going from node ui to node vi becomes a
 * directed edge going from node vi to node ui.
 *
 * For every node i in the range [0, n - 1], your task is to independently calculate the minimum number of edge
 * reversals required so it is possible to each any other node starting from node i through a sequence of directed
 * edges.
 *
 * Return an integer array answer, where answer[i] is the minimum number of edge reversals required so it is possible to
 * reach any other nodes starting from node i through a sequence of directed edges.
 *
 * ! 2 <= n <= 10^5
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ui == edges[i][0] < n
 * ! 0 <= vi == edges[i][1] < n
 * ! ui != vi
 * ! The input is generated such that if the edges were bi-directional, the graph would be a tree.
 */

class Solution {
public:
    std::vector<int> minEdgeReversals(int n, std::vector<std::vector<int>>& edges)
    {
        Graph graph(n);
        for (const auto& e : edges) {
            graph[e[0]].emplace_back(e[1], 1);
            graph[e[1]].emplace_back(e[0], -1);
        }
        std::vector<int> result(n, 0);
        dfs1(result, 0, -1, graph);
        dfs2(result, 0, -1, graph);
        return result;
    }

private:
    using Graph = std::vector<std::vector<std::pair<int, int>>>;

    void dfs1(std::vector<int>& result, int node, int parent, const Graph& graph)
    {
        for (const auto& [next, w] : graph[node]) {
            if (next == parent)
                continue;

            if (w < 0) {
                result[0]++;
            }
            dfs1(result, next, node, graph);
        }
    }

    void dfs2(std::vector<int>& result, int node, int parent, const Graph& graph)
    {
        for (const auto& [next, w] : graph[node]) {
            if (next == parent)
                continue;

            result[next] = result[node] + w;
            dfs2(result, next, node, graph);
        }
    }
};