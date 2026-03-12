#include <algorithm>
#include <array>
#include <vector>

/**
 * You are given an integer n, representing n nodes numbered from 0 to n - 1 and a list of edges, where edges[i] = [ui,
 * vi, si, musti]:
 *
 * - ui and vi indicates an undirected edge between nodes ui and vi.
 *
 * - si is the strength of the edge.
 *
 * - musti is an integer (0 or 1). If musti == 1, the edge must be included in the spanning tree. These edges cannot be
 * upgraded.
 *
 * You are also given an integer k, the maximum number of upgrades you can perform. Each upgrade doubles the strength of
 * an edge, and each eligible edge (with musti == 0) can be upgraded at most once.
 *
 * The stability of a spanning tree is defined as the minimum strength score among all edges included in it.
 *
 * Return the maximum possible stability of any valid spanning tree. If it is impossible to connect all nodes, return
 * -1.
 *
 * Note: A spanning tree of a graph with n nodes is a subset of the edges that connects all nodes together (i.e. the
 * graph is connected) without forming any cycles, and uses exactly n - 1 edges.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : n(n), root(n), size(n, 1)
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

    void connect(int p, int q)
    {
        auto rootP = find(p);
        auto rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
        n--;
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    int numOfConnectedComponents()
    {
        return n;
    }

private:
    int n;
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int maxStability(int n, std::vector<std::vector<int>>& edges, int k)
    {
        UnionFind uf(n);
        std::vector<std::array<int, 3>> optional;
        int hi = INT_MAX;
        for (const auto& e : edges) {
            if (e[3] == 0) {
                optional.push_back({e[0], e[1], e[2]});
                continue;
            }
            if (uf.isConnected(e[0], e[1]))
                return -1;

            uf.connect(e[0], e[1]);
            hi = std::min(hi, e[2]);
        }
        if (uf.numOfConnectedComponents() == 1)
            return hi;

        std::sort(optional.begin(), optional.end(),
                  [](const auto& e1, const auto& e2) { return std::get<2>(e1) > std::get<2>(e2); });
        int lo = 0;
        while (lo <= hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, k, optional, uf)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(int min, int k, const std::vector<std::array<int, 3>>& edges, UnionFind uf)
    {
        for (const auto& [u, v, w] : edges) {
            if (uf.isConnected(u, v))
                continue;

            if (w >= min) {
                uf.connect(u, v);
            } else if (k > 0 && 2 * w >= min) {
                uf.connect(u, v);
                k--;
            } else {
                break;
            }
            if (uf.numOfConnectedComponents() == 1)
                return true;
        }
        return false;
    }
};