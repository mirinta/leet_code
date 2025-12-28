#include <vector>

/**
 * There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given
 * the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates
 * that there is an edge between nodes ai and bi in the tree.
 *
 * Each node has an associated price. You are given an integer array price, where price[i] is the
 * price of the ith node.
 *
 * The price sum of a given path is the sum of the prices of all nodes lying on that path.
 *
 * Additionally, you are given a 2D integer array trips, where trips[i] = [starti, endi] indicates
 * that you start the ith trip from the node starti and travel to the node endi by any path you
 * like.
 *
 * Before performing your first trip, you can choose some non-adjacent nodes and halve the prices.
 *
 * Return the minimum total price sum to perform all the given trips.
 *
 * ! 1 <= n <= 50
 * ! edges.length == n - 1
 * ! 0 <= ai, bi <= n - 1
 * ! edges represents a valid tree.
 * ! price.length == n
 * ! price[i] is an even integer.
 * ! 1 <= price[i] <= 1000
 * ! 1 <= trips.length <= 100
 * ! 0 <= starti, endi <= n - 1
 */

class Solution {
public:
    int minimumTotalPrice(int n,
                          std::vector<std::vector<int>>& edges,
                          std::vector<int>& price,
                          std::vector<std::vector<int>>& trips)
    {
        Graph graph(n);
        for (const auto& edge : edges) {
            const auto v = edge[0];
            const auto w = edge[1];
            graph[v].push_back(w);
            graph[w].push_back(v);
        }
        std::vector<int> count(n, 0); // count[i] = num of times that vertex i is visited
        for (const auto& trip : trips) {
            const auto from = trip[0];
            const auto to = trip[1];
            dfs(count, from, -1, to, graph);
        }
        const auto [notHalved, halved] = dfs(0, -1, count, price, graph);
        return std::min(notHalved, halved);
    }

private:
    using Graph = std::vector<std::vector<int>>;

    bool dfs(std::vector<int>& count, int current, int parent, int target, const Graph& graph)
    {
        if (current == target) {
            count[target]++;
            return true;
        }

        for (const auto& child : graph[current]) {
            if (child == parent)
                continue;

            if (dfs(count, child, current, target, graph)) {
                count[current]++;
                return true;
            }
        }
        return false;
    }

    // similar to LC.337
    // return <min cost if current is not halved, min cost if current is halved>
    std::pair<int, int>
        dfs(int current, int parent, const std::vector<int>& count, const std::vector<int>& price, const Graph& graph)
    {
        int notHalved = price[current] * count[current];
        int halved = price[current] * count[current] / 2;
        for (const auto& child : graph[current]) {
            if (child == parent)
                continue;

            const auto [childNotHalved, childHalved] = dfs(child, current, count, price, graph);
            notHalved += std::min(childNotHalved, childHalved);
            halved += childNotHalved;
        }
        return {notHalved, halved};
    }
};
