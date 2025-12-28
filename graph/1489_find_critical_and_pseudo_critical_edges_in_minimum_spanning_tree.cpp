#include <algorithm>
#include <vector>

/**
 * Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an
 * array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge
 * between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that
 * connects all vertices without cycles and with the minimum possible total edge weight.
 *
 * Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST).
 * An MST edge whose deletion from the graph would cause the MST weight to increase is called a
 * critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs
 * but not all.
 *
 * Note that you can return the indices of the edges in any order.
 *
 * ! 2 <= n <= 100
 * ! 1 <= edges.length <= min(200, n * (n - 1) / 2)
 * ! edges[i].length == 3
 * ! 0 <= ai < bi < n
 * ! 1 <= weighti <= 1000
 * ! All pairs (ai, bi) are distinct.
 */

class UnionFind {
public:
    explicit UnionFind(int n) : count(n), root(n), rank(n)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
            rank[i] = 1;
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

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (rank[rootP] > rank[rootQ]) {
            root[rootQ] = rootP;
        } else if (rank[rootP] < rank[rootQ]) {
            root[rootP] = rootQ;
        } else {
            root[rootQ] = rootP;
            rank[rootP]++;
        }
        count--;
    }

private:
    int count;
    std::vector<int> root;
    std::vector<int> rank;
};

class Solution {
public:
    std::vector<std::vector<int>> findCriticalAndPseudoCriticalEdges(int n, std::vector<std::vector<int>>& edges)
    {
        // store original indices
        // edges[i] = {vertex_a, vertex_b, weight, original_index}
        for (int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
        }
        std::sort(edges.begin(), edges.end(), [](const auto& e1, const auto& e2) { return e1[2] < e2[2]; });
        const int mst = totalWeightOfMST(n, edges);
        std::vector<int> critical;
        std::vector<int> pseudoCritical;
        // critical edge: the total weight of MST will increase if the edge is ignored.
        // pseudo-critical edge: the total weight of MST keeps the same if the edge must be used.
        for (int i = 0; i < edges.size(); ++i) {
            if (totalWeightOfMST(n, edges, -1, i) > mst) {
                critical.push_back(edges[i][3]);
            } else if (totalWeightOfMST(n, edges, i, -1) == mst) {
                pseudoCritical.push_back(edges[i][3]);
            }
        }
        return {critical, pseudoCritical};
    }

private:
    int totalWeightOfMST(int n, const std::vector<std::vector<int>>& edges, int forceEdge = -1, int ignoreEdge = -1)
    {
        UnionFind uf(n);
        int result = 0;
        if (forceEdge >= 0 && forceEdge < edges.size()) {
            uf.connect(edges[forceEdge][0], edges[forceEdge][1]);
            result += edges[forceEdge][2];
        }
        for (int i = 0; i < edges.size(); ++i) {
            if (ignoreEdge == i || forceEdge == i)
                continue;

            const auto& p = edges[i][0];
            const auto& q = edges[i][1];
            const auto& w = edges[i][2];
            if (!uf.isConnected(p, q)) {
                result += w;
                uf.connect(p, q);
            }
        }
        return uf.numOfConnectedComponents() == 1 ? result : INT_MAX;
    }
};