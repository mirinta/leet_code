#include <vector>

/**
 * There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1
 * (inclusive). The edges in the graph are represented as a 2D integer array edges, where each
 * edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex
 * pair is connected by at most one edge, and no vertex has an edge to itself.
 *
 * You want to determine if there is a valid path that exists from vertex source to vertex
 * destination.
 *
 * Given edges and the integers n, source, and destination, return true if there is a valid path
 * from source to destination, or false otherwise.
 *
 * ! 1 <= n <= 2 * 10^5
 * ! 0 <= edges.length <= 2 * 10^5
 * ! edges[i].length == 2
 * ! 0 <= ui, vi <= n - 1
 * ! ui != vi
 * ! 0 <= source, destination <= n - 1
 * ! There are no duplicate edges.
 * ! There are no self edges.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (root[x] != x) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    void connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootQ] > rank[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        rank[rootP] += rank[rootQ];
    }

private:
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        return approach2(n, edges, source, destination);
    }

private:
    bool approach2(int n, const std::vector<std::vector<int>>& edges, int source, int destination)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            uf.connect(edge[0], edge[1]);
        }
        return uf.isConnected(source, destination);
    }

    bool approach1(int n, const std::vector<std::vector<int>>& edges, int source, int destination)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        std::vector<bool> visited(n, false);
        return dfs(visited, source, destination, graph);
    }

    bool dfs(std::vector<bool>& visited, int i, int destination, const std::vector<std::vector<int>>& graph)
    {
        if (i == destination)
            return true;

        visited[i] = true;
        for (const auto& adj : graph[i]) {
            if (!visited[adj] && dfs(visited, adj, destination, graph))
                return true;
        }
        return false;
    }
};