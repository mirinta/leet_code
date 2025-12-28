#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n
 * - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists
 * an undirected edge connecting vertices ai and bi.
 *
 * Return the number of complete connected components of the graph.
 *
 * A connected component is a subgraph of a graph in which there exists a path between any two
 * vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
 *
 * A connected component is said to be complete if there exists an edge between every pair of its
 * vertices.
 *
 * ! 1 <= n <= 50
 * ! 0 <= edges.length <= n * (n - 1) / 2
 * ! edges[i].length == 2
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 * ! There are no repeated edges.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        std::iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    void connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
    }

    int sizeOfGroup(int x)
    {
        return size[find(x)];
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int countCompleteComponents(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& e : edges) {
            uf.connect(e[0], e[1]);
        }
        std::unordered_map<int, int> map;
        for (const auto& e : edges) {
            map[uf.find(e[0])]++;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (i != uf.find(i))
                continue;

            const int m = uf.sizeOfGroup(i);
            result += map[uf.find(i)] == m * (m - 1) / 2;
        }
        return result;
    }
};