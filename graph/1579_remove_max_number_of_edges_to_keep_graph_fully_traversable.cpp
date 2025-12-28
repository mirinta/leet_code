#include <array>
#include <vector>

/**
 * Alice and Bob have an undirected graph of n nodes and three types of edges:
 *
 * - Type 1: Can be traversed by Alice only.
 *
 * - Type 2: Can be traversed by Bob only.
 *
 * - Type 3: Can be traversed by both Alice and Bob.
 *
 * Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type
 * typei between nodes ui and vi, find the maximum number of edges you can remove so that after
 * removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is
 * fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
 *
 * Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully
 * traverse the graph.
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
 * ! edges[i].length == 3
 * ! 1 <= typei <= 3
 * ! 1 <= ui < vi <= n
 * ! All tuples (typei, ui, vi) are distinct.
 */

class UnionFind {
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

    int numOfConnectedComponents()
    {
        return count;
    }

    bool connect(int p, int q)
    {
        auto rootP = find(p);
        auto rootQ = find(q);
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
    int count;
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::array<int, 2>> edge1;
        std::vector<std::array<int, 2>> edge2;
        std::vector<std::array<int, 2>> edge3;
        for (const auto& e : edges) {
            if (e[0] == 1) {
                edge1.push_back({e[1] - 1, e[2] - 1});
            } else if (e[0] == 2) {
                edge2.push_back({e[1] - 1, e[2] - 1});
            } else {
                edge3.push_back({e[1] - 1, e[2] - 1});
            }
        }
        int count1 = 0; // num of used edges of type 1
        int count2 = 0; // num of used edges of type 2
        int count3 = 0; // num of used edges of type 3
        UnionFind uf(n);
        for (const auto& [p, q] : edge3) {
            count3 += uf.connect(p, q);
        }
        if (uf.numOfConnectedComponents() == 1)
            return edges.size() - count3;

        auto uf1 = uf;
        for (const auto& [p, q] : edge1) {
            count1 += uf1.connect(p, q);
        }
        if (uf1.numOfConnectedComponents() != 1)
            return -1;

        auto uf2 = uf;
        for (const auto& [p, q] : edge2) {
            count2 += uf2.connect(p, q);
        }
        if (uf2.numOfConnectedComponents() != 1)
            return -1;

        return edges.size() - count1 - count2 - count3;
    }
};