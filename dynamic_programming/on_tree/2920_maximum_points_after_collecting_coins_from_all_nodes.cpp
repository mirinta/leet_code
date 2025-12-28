#include <algorithm>
#include <vector>

/**
 * There exists an undirected tree rooted at node 0 with n nodes labeled from 0 to n - 1. You are
 * given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is
 * an edge between nodes ai and bi in the tree. You are also given a 0-indexed array coins of size n
 * where coins[i] indicates the number of coins in the vertex i, and an integer k.
 *
 * Starting from the root, you have to collect all the coins such that the coins at a node can only
 * be collected if the coins of its ancestors have been already collected.
 *
 * Coins at nodei can be collected in one of the following ways:
 *
 * - Collect all the coins, but you will get coins[i] - k points. If coins[i] - k is negative then
 * you will lose abs(coins[i] - k) points.
 *
 * - Collect all the coins, but you will get floor(coins[i] / 2) points. If this way is used, then
 * for all the nodej present in the subtree of nodei, coins[j] will get reduced to floor(coins[j] /
 * 2).
 *
 * Return the maximum points you can get after collecting the coins from all the tree nodes.
 *
 * ! n == coins.length
 * ! 2 <= n <= 10^5
 * ! 0 <= coins[i] <= 10^4
 * ! edges.length == n - 1
 * ! 0 <= edges[i][0], edges[i][1] < n
 * ! 0 <= k <= 10^4
 */

class Solution {
public:
    int maximumPoints(std::vector<std::vector<int>>& edges, std::vector<int>& coins, int k)
    {
        // option2: floor(coins[i] / 2) is equivalent to coins[i] >> 1
        // we can track the num of choosing option2 from ancestors to node i,
        // then the value of node i becomes coins[i] >> #numOfOption2
        const int n = coins.size();
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        maxShifts = numOfBits(*std::max_element(coins.begin(), coins.end()));
        memo.resize(n, std::vector<int>(maxShifts, -1));
        return dfs(0, -1, 0, coins, k, graph);
    }

private:
    int maxShifts{0};
    std::vector<std::vector<int>> memo;

    int numOfBits(int n)
    {
        int count = 0;
        while (n) {
            count++;
            n >>= 1;
        }
        return count;
    }

    int dfs(int root,
            int parent,
            int numOfOption2,
            const std::vector<int>& coins,
            int k,
            const std::vector<std::vector<int>>& graph)
    {
        if (numOfOption2 >= maxShifts)
            return 0;

        if (memo[root][numOfOption2] != -1)
            return memo[root][numOfOption2];

        int option1 = (coins[root] >> numOfOption2) - k;
        int option2 = coins[root] >> (numOfOption2 + 1);
        for (const auto& child : graph[root]) {
            if (child == parent)
                continue;

            option1 += dfs(child, root, numOfOption2, coins, k, graph);
            option2 += dfs(child, root, numOfOption2 + 1, coins, k, graph);
        }
        memo[root][numOfOption2] = std::max(option1, option2);
        return memo[root][numOfOption2];
    }
};
