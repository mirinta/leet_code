#include <queue>
#include <vector>

/**
 * There is an undirected tree with n nodes labeled from 1 to n,
 * rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi]
 * indicates that there is an edge between nodes ui and vi.
 *
 * Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
 *
 * The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
 *
 * Select any one node x at the maximum depth. Return the number of ways to assign ede weights in the path from node 1
 * to x such that its total cost is odd.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * Note: Ignore all edges not in the path from node 1 to x.
 *
 * ! 2 <= n <= 10^5
 * ! edges.length == n - 1
 * ! edges[i] == [ui, vi]
 * ! 1 <= ui, vi <= n
 * ! edges represents a valid tree.
 */

class Solution {
public:
    int assignEdgeWeights(std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0] - 1].emplace_back(e[1] - 1);
            graph[e[1] - 1].emplace_back(e[0] - 1);
        }
        int levels = 0;
        std::queue<int> queue;
        queue.emplace(0);
        std::vector<bool> visited(n, false);
        visited[0] = true;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& w : graph[v]) {
                    if (!visited[w]) {
                        queue.emplace(w);
                        visited[w] = true;
                    }
                }
            }
            levels++;
        }
        // dp[i][0] = num of ways to make the sum of i numbers to be even
        // dp[i][1] = num of ways to make the sum of i numbers to be odd
        // dp[0][0] = 1 and dp[0][1] = 1
        // dp[i][0] = dp[i - 1][0] + dp[i - 1][1]
        // dp[i][1] = dp[i - 1][0] + dp[i - 1][1]
        // (1,0) -> (1,1) -> (2,2) -> (4,4) -> (8,8) -> ...
        // thus, answer = 2^(levels - 2)
        return fastPowMod(2, levels - 2, 1e9 + 7);
    }

private:
    long long fastPowMod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};