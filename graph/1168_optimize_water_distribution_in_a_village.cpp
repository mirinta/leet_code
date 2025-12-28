#include <algorithm>
#include <queue>
#include <vector>

/**
 * There are n houses in a village. We want to supply water for all the houses by building wells and
 * laying pipes.
 *
 * For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the
 * -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between
 * houses are given by the array pipes where each pipes[j] = [house1j, house2j, costj] represents
 * the cost to connect house1j and house2j together using a pipe. Connections are bidirectional, and
 * there could be multiple valid connections between the same two houses with different costs.
 *
 * Return the minimum total cost to supply water to all houses.
 *
 * ! 2 <= n <= 10^4
 * ! wells.length == n
 * ! 0 <= wells[i] <= 10^5
 * ! 1 <= pipes.length <= 10^4
 * ! pipes[j].length == 3
 * ! 1 <= house1j, house2j <= n
 * ! 0 <= costj <= 10^5
 * ! house1j != house2j
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
    int minCostToSupplyWater(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        return approach2(n, wells, pipes);
    }

private:
    // Prim's algorithm
    int approach2(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        using Pair = std::pair<int, int>; // <cost, vertex>
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        std::vector<std::vector<Pair>> graph(n + 1);
        for (int i = 0; i < wells.size(); ++i) {
            graph[0].emplace_back(wells[i], i + 1);
            graph[i + 1].emplace_back(wells[i], 0);
            pq.push(graph[0].back());
        }
        for (const auto& pipe : pipes) {
            const auto& from = pipe[0];
            const auto& to = pipe[1];
            const auto& cost = pipe[2];
            graph[from].emplace_back(cost, to);
            graph[to].emplace_back(cost, from);
        }
        std::vector<bool> visited(n + 1, false);
        visited[0] = true;
        int result = 0;
        while (!pq.empty()) {
            const auto [cost, v] = pq.top();
            pq.pop();
            if (visited[v])
                continue;

            visited[v] = true;
            result += cost;
            for (const auto& p : graph[v]) {
                if (!visited[p.second]) {
                    pq.push(p);
                }
            }
        }
        return result;
    }

    // Kruskal's algorithm
    int approach1(int n, std::vector<int>& wells, std::vector<std::vector<int>>& pipes)
    {
        // a virtual vertex denotes the source of water, index of this vertex is 0
        for (int i = 0; i < wells.size(); ++i) {
            pipes.push_back({0, i + 1, wells[i]});
        }
        std::sort(pipes.begin(), pipes.end(), [](const auto& v1, const auto& v2) { return v1[2] < v2[2]; });
        UnionFind uf(n + 1);
        int result = 0;
        for (const auto& pipe : pipes) {
            const auto& from = pipe[0];
            const auto& to = pipe[1];
            const auto& cost = pipe[2];
            if (!uf.isConnected(from, to)) {
                result += cost;
                uf.connect(from, to);
            }
        }
        return result;
    }
};
