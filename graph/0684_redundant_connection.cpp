#include <vector>

/**
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 *
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with one
 * additional edge added. The added edge has two different vertices chosen from 1 to n, and was not
 * an edge that already existed. The graph is represented as an array edges of length n where
 * edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
 *
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are
 * multiple answers, return the answer that occurs last in the input.
 *
 * ! n == edges.length
 * ! 3 <= n <= 1000
 * ! edges[i].length == 2
 * ! 1 <= ai < bi <= edges.length
 * ! ai != bi
 * ! There are no repeated edges.
 * ! The given graph is connected.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool connect(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return false;

        if (size[rootQ] > size[rootP]) {
            std::swap(rootP, rootQ);
        }
        root[rootQ] = rootP;
        size[rootP] += size[rootQ];
        return true;
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size();
        UnionFind uf(n + 1);
        std::vector<int> result;
        for (const auto& edge : edges) {
            if (!uf.connect(edge[0], edge[1])) {
                result = {edge[0], edge[1]};
            }
        }
        return result;
    }
};