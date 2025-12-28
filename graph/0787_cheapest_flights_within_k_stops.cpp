#include <queue>
#include <tuple>
#include <vector>

/**
 * There are n cities connected by some number of flights. You are given an array flights where
 * flights[i] = [from_i, to_i, price_i] indicates that there is a flight from city from_i to city
 * to_i with cost price_i.
 *
 * You are also given three integers src, dst, and k, return the cheapest price from src to dst with
 * at most k stops. If there is no such route, return -1.
 *
 * ! 1 <= n <= 100
 * ! 0 <= flights.length <= (n * (n - 1) / 2)
 * ! flights[i].length == 3
 * ! 0 <= from_i, to_i < n
 * ! from_i != to_i
 * ! 1 <= price_i <= 10^4
 * ! There will not be any multiple flights between two cities.
 * ! 0 <= src, dst, k < n
 * ! src != dst
 */

class Solution {
public:
    int findCheapestPrice(int n, std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        return approach3(n, flights, src, dst, k);
    }

private:
    // DP with space optimization (Bellman-Ford), TC = O(K(N+E)), SC = O(N)
    int approach3(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        std::vector<int> dp(n, INT_MAX);
        dp[src] = 0;
        std::vector<int> prev(n);
        int result = INT_MAX;
        for (int i = 1; i <= k + 1; ++i) {
            bool update = false;
            prev.assign(dp.begin(), dp.end());
            std::fill(dp.begin(), dp.end(), INT_MAX);
            for (const auto& flight : flights) {
                const int from = flight[0];
                const int to = flight[1];
                const int price = flight[2];
                if (prev[from] != INT_MAX && prev[from] + price < dp[to]) {
                    dp[to] = prev[from] + price;
                    update = true;
                }
            }
            if (!update)
                break;

            result = std::min(result, dp[dst]);
        }
        return result == INT_MAX ? -1 : result;
    }

    // DP, TC = O(KE), SC = O(KN)
    int approach2(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        // dp[i][j] = min cost from src to j with at most i edges
        std::vector<std::vector<int>> dp(k + 2, std::vector<int>(n, INT_MAX));
        dp[0][src] = 0;
        int result = INT_MAX;
        for (int i = 1; i <= k + 1; ++i) {
            bool update = false;
            for (const auto& flight : flights) {
                const int from = flight[0];
                const int to = flight[1];
                const int price = flight[2];
                if (dp[i - 1][from] != INT_MAX && dp[i - 1][from] + price < dp[i][to]) {
                    dp[i][to] = dp[i - 1][from] + price;
                    update = true;
                }
            }
            if (!update)
                break;

            result = std::min(result, dp[i][dst]);
        }
        return result == INT_MAX ? -1 : result;
    }

    // similar to Dijkstra, TC = O(E + EKlog(EK)), SC = O(E + N + EK)
    int approach1(int n, const std::vector<std::vector<int>>& flights, int src, int dst, int k)
    {
        // at most k stops = at most edges from src to dst
        std::vector<std::vector<std::pair<int, int>>> graph(n); // <to, price>
        for (const auto& flight : flights) {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }
        std::vector<int> edgesTo(n, INT_MAX);
        edgesTo[src] = 0;
        using Triplets = std::tuple<int, int, int>; // <cost, edges, v>
        auto comparator = [](const auto& t1, const auto& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Triplets, std::vector<Triplets>, decltype(comparator)> pq(comparator);
        pq.emplace(0, 0, src);
        while (!pq.empty()) {
            const auto [cost, edges, v] = pq.top();
            pq.pop();
            if (edges > k + 1 || edges > edgesTo[v])
                continue;

            if (v == dst)
                return cost;

            edgesTo[v] = edges;
            for (const auto& [w, price] : graph[v]) {
                pq.emplace(cost + price, edges + 1, w);
            }
        }
        return -1;
    }
};
