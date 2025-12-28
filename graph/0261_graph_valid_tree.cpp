#include <vector>

/**
 * You have a graph of "n" nodes labeled from 0 to n - 1.
 *
 * You are given an integer n and a list of "edges" where edges[i] = [ai, bi] indicates that there
 * is an undirected edge between nodes ai and bi in the graph.
 *
 * Return true if the edges of the given graph make up a valid tree, and false otherwise.
 *
 * ! 1 <= n <= 2000
 * ! 0 <= edges.length <= 5000
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! There are no self-loops or repeated edges.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1), count(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int numOfConnectedComponents() const
    {
        return count;
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
        count--;
        return true;
    }

private:
    std::vector<int> root;
    std::vector<int> size;
    int count;
};

class Solution {
public:
    bool validTree(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            if (!uf.connect(edge[0], edge[1]))
                return false;
        }
        return uf.numOfConnectedComponents() == 1;
    }
};