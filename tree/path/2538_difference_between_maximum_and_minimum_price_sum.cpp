#include <vector>

/**
 * There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You
 * are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi]
 * indicates that there is an edge between nodes ai and bi in the tree.
 *
 * Each node has an associated price. You are given an integer array price, where price[i] is the
 * price of the ith node.
 *
 * The price sum of a given path is the sum of the prices of all nodes lying on that path.
 *
 * The tree can be rooted at any node root of your choice. The incurred cost after choosing root is
 * the difference between the maximum and minimum price sum amongst all paths starting at root.
 *
 * Return the maximum possible cost amongst all possible root choices.
 *
 * ! 1 <= n <= 10^5
 * ! edges.length == n - 1
 * ! 0 <= ai, bi <= n - 1
 * ! edges represents a valid tree.
 * ! price.length == n
 * ! 1 <= price[i] <= 10^5
 */

class Solution {
public:
    long long maxOutput(int n, std::vector<std::vector<int>>& edges, std::vector<int>& price)
    {
        Graph graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int result = 0;
        dfs(result, 0, -1, price, graph);
        return result;
    }

private:
    using Graph = std::vector<std::vector<int>>;

    std::pair<int, int> dfs(int& result, int root, int parent, const std::vector<int>& price, const Graph& graph)
    {
        // node x is a leaf if graph[x].size() == 1 && graph[x][0] = parent
        int maxWithRoot = price[root];
        int maxWithoutRoot = 0;
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            const auto [withChild, withoutChild] = dfs(result, child, root, price, graph);
            result = std::max({result, maxWithRoot + withoutChild, maxWithoutRoot + withChild});
            maxWithRoot = std::max(maxWithRoot, withChild + price[root]);
            maxWithoutRoot = std::max(maxWithoutRoot, withoutChild + price[root]);
        }
        return {maxWithRoot, maxWithoutRoot};
    }
};