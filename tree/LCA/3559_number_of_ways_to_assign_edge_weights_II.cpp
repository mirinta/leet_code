#include <array>
#include <functional>
#include <vector>

/**
 * There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D
 * integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and
 * vi.
 *
 * Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
 *
 * The cost of a path between any two nodes u and v is the total weight all edges in the path connecting them.
 *
 * You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign
 * weights to edges in the path such that the cost of the path between ui and vi is odd.
 *
 * Return an array answer, where answer[i] is the number of valid assignments for queries[i].
 *
 * Since the answer may be large, apply modulo 1e9 + 7 to each answer[i].
 *
 * Note: For each query, disregard all edges not in the path between node ui and vi.
 *
 * ! 2 <= n <= 10^5
 * ! edges.length == n - 1
 * ! edges[i] == [ui, vi]
 * ! 1 <= queries.length <= 10^5
 * ! queries[i] == [ui, vi]
 * ! 1 <= ui, vi <= n
 * ! edges represents a valid tree.
 */

class LCABinaryLifting {
public:
    explicit LCABinaryLifting(int root, int n, const std::vector<std::vector<int>>& graph)
        : parent(n, std::vector<int>(std::ceil(std::log(n) / std::log(2)), -1)), depth(n, 0)
    {
        std::function<void(int, int)> dfs = [&](int curr, int prev) {
            parent[curr][0] = prev;
            for (const auto& next : graph[curr]) {
                if (next == prev)
                    continue;

                depth[next] = depth[curr] + 1;
                dfs(next, curr);
            }
        };
        dfs(root, -1);
        for (int i = 0; i < parent[0].size() - 1; ++i) {
            for (int x = 0; x < n; ++x) {
                if (const int p = parent[x][i]; p != -1) {
                    parent[x][i + 1] = parent[p][i];
                }
            }
        }
    }

    int getKthAncestor(int x, int k)
    {
        for (int i = 0; i < parent[x].size(); ++i) {
            if (k & (1 << i)) {
                x = parent[x][i];
            }
        }
        return x;
    }

    int lca(int x, int y)
    {
        if (depth[x] > depth[y]) {
            std::swap(x, y);
        }
        y = getKthAncestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;

        for (int i = parent[x].size() - 1; i >= 0; --i) {
            if (parent[x][i] == -1 || parent[x][i] == parent[y][i])
                continue;

            x = parent[x][i];
            y = parent[y][i];
        }
        return parent[x][0];
    }

    int dist(int x, int y)
    {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

private:
    std::vector<std::vector<int>> parent;
    std::vector<int> depth;
};

class Solution {
public:
    std::vector<int> assignEdgeWeights(std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& queries)
    {
        static constexpr auto powOf2 = []() {
            static constexpr long long kMod = 1e9 + 7;
            std::array<long long, 100000> result{};
            result[0] = 1;
            for (long long i = 1; i < result.size(); ++i) {
                result[i] = result[i - 1] * 2 % kMod;
            }
            return result;
        }();
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0] - 1].emplace_back(e[1] - 1);
            graph[e[1] - 1].emplace_back(e[0] - 1);
        }
        LCABinaryLifting tree(0, n, graph);
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            if (q[0] == q[1]) {
                result.push_back(0);
            } else {
                result.push_back(powOf2[tree.dist(q[0] - 1, q[1] - 1) - 1]);
            }
        }
        return result;
    }
};