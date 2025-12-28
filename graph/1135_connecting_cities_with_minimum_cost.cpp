#include <algorithm>
#include <queue>
#include <vector>

/**
 * There are "n" cities labeled from 1 to n.
 *
 * You are given the integer n and an array "connections" where connections[i] = [x_i, y_i, cost_i]
 * indicates that the cost of connecting city x_i and city y_i (bidirectional connection) is cost_i.
 *
 * Return the minimum cost to connect all the n cities such that there is at least one path between
 * each pair of cities. If it is impossible to connect all the n cities, return -1.
 *
 * The cost is the sum of the connection's costs used.
 *
 * ! 1 <= n <= 10^4
 * ! 1 <= connections.length <= 10^4
 * ! connections[i].length == 3
 * ! 1 <= xi, yi <= n
 * ! xi != yi
 * ! 0 <= cost_i <= 10^5
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
    int minimumCost(int n, std::vector<std::vector<int>>& connections)
    {
        return approach2(n, connections);
    }

private:
    // Prim's algorithm
    int approach2(int n, std::vector<std::vector<int>>& connections)
    {
        using Pair = std::pair<int, int>; // <cost, vertex>
        std::vector<std::vector<Pair>> graph(n);
        for (const auto& edge : connections) {
            const auto& from = edge[0] - 1;
            const auto& to = edge[1] - 1;
            const auto& cost = edge[2];
            graph[from].emplace_back(cost, to);
            graph[to].emplace_back(cost, from);
        }
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator); // min heap
        // start from vertex 0
        for (const auto& p : graph[0]) {
            pq.push(p);
        }
        std::vector<bool> visited(n, false);
        visited[0] = true;
        int result = 0;
        int edges = 0; // the MST requires n-1 edges
        while (!pq.empty()) {
            const auto [cost, v] = pq.top();
            pq.pop();
            if (visited[v])
                continue;

            visited[v] = true;
            result += cost;
            edges++;
            for (const auto& p : graph[v]) {
                if (!visited[p.second]) {
                    pq.push(p);
                }
            }
        }
        return edges == n - 1 ? result : -1;
    }

    // Kruskal's algorithm
    int approach1(int n, std::vector<std::vector<int>>& connections)
    {
        std::sort(connections.begin(), connections.end(), [](const auto& e1, const auto& e2) { return e1[2] < e2[2]; });
        UnionFind uf(n);
        int result = 0;
        for (const auto& edge : connections) {
            const auto& from = edge[0] - 1;
            const auto& to = edge[1] - 1;
            const auto& cost = edge[2];
            if (!uf.isConnected(from, to)) {
                uf.connect(from, to);
                result += cost;
            }
        }
        return uf.numOfConnectedComponents() == 1 ? result : -1;
    }
};
