#include <algorithm>
#include <vector>

/**
 * You are given an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You
 * are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that
 * there is an edge between nodes ai and bi in the tree.
 *
 * You are also given a 0-indexed integer array cost of length n, where cost[i] is the cost assigned
 * to the ith node.
 *
 * You need to place some coins on every node of the tree. The number of coins to be placed at node
 * i can be calculated as:
 *
 * If size of the subtree of node i is less than 3, place 1 coin.
 * Otherwise, place an amount of coins equal to the maximum product of cost values assigned to 3
 * distinct nodes in the subtree of node i. If this product is negative, place 0 coins. Return an
 * array coin of size n such that coin[i] is the number of coins placed at node i.
 *
 * ! 2 <= n <= 2 * 10^4
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! cost.length == n
 * ! 1 <= |cost[i]| <= 10^4
 * ! The input is generated such that edges represents a valid tree.
 */

class Solution {
public:
    std::vector<long long> placedCoins(std::vector<std::vector<int>>& edges, std::vector<int>& cost)
    {
        const int n = cost.size();
        Tree tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        std::vector<LL> result(n);
        dfs(result, 0, -1, tree, cost);
        return result;
    }

private:
    using Tree = std::vector<std::vector<int>>;
    using LL = long long;

    // return at most 5 values: {max, secondMax, thirdMax, secondMin, min} in the subtree of node i
    std::vector<LL> dfs(std::vector<LL>& result, int i, int parent, const Tree& tree, const std::vector<int>& cost)
    {
        std::vector<long long> values{cost[i]};
        for (const auto& child : tree[i]) {
            if (child == parent)
                continue;

            const auto subproblem = dfs(result, child, i, tree, cost);
            values.insert(values.end(), subproblem.begin(), subproblem.end());
        }
        const int n = values.size();
        if (n < 3) {
            result[i] = 1;
            return values;
        }
        std::sort(values.begin(), values.end(), std::greater<>());
        result[i] = std::max({0LL, values[0] * values[1] * values[2], values[n - 1] * values[n - 2] * values[0]});
        if (n <= 5)
            return values;

        return {values[0], values[1], values[2], values[n - 2], values[n - 1]};
    }
};