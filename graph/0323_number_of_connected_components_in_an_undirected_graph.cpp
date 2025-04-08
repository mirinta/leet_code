#include <vector>

/**
 * You have a graph of "n" nodes. You are given an integer "n" and an array "edges" where edges[i] =
 * [ai, bi] indicates that there is an edge between ai and bi in the graph.
 *
 * Return the number of connected components in the graph.
 *
 * ! 1 <= n <= 2000
 * ! 1 <= edges.length <= 5000
 * ! edges[i].length == 2
 * ! 0 <= ai <= bi < n
 * ! ai != bi
 * ! There are no repeated edges.
 */

class UnionFind
{
public:
    explicit UnionFind(int n) : count(n), root(n), size(n, 1)
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
        count--;
    }

    int numOfConnectedComponents() { return count; }

private:
    int count;
    std::vector<int> root;
    std::vector<int> size;
};

class Solution
{
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges)
    {
        UnionFind uf(n);
        for (const auto& e : edges) {
            uf.connect(e[0], e[1]);
        }
        return uf.numOfConnectedComponents();
    }
};
