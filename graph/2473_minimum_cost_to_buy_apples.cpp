#include <queue>
#include <vector>

/**
 * You are given a positive integer n representing n cities numbered from 1 to n. You are also given
 * a 2D array roads, where roads[i] = [ai, bi, costi] indicates that there is a bidirectional road
 * between cities ai and bi with a cost of traveling equal to costi.
 *
 * You can buy apples in any city you want, but some cities have different costs to buy apples. You
 * are given the 1-based array appleCost where appleCost[i] is the cost of buying one apple from
 * city i.
 *
 * You start at some city, traverse through various roads, and eventually buy exactly one apple from
 * any city. After you buy that apple, you have to return back to the city you started at, but now
 * the cost of all the roads will be multiplied by a given factor k.
 *
 * Given the integer k, return a 1-based array answer of size n where answer[i] is the minimum total
 * cost to buy an apple if you start at city i.
 *
 * ! 2 <= n <= 1000
 * ! 1 <= roads.length <= 1000
 * ! 1 <= ai, bi <= n
 * ! ai != bi
 * ! 1 <= costi <= 10^5
 * ! appleCost.length == n
 * ! 1 <= appleCost[i] <= 10^5
 * ! 1 <= k <= 100
 * ! There are no repeated edges.
 */

class Solution {
public:
    std::vector<long long> minCost(int n, std::vector<std::vector<int>>& roads, std::vector<int>& appleCost, int k)
    {
        std::vector<std::vector<Pair>> graph(n);
        for (const auto& road : roads) {
            graph[road[0] - 1].emplace_back(road[1] - 1, road[2]);
            graph[road[1] - 1].emplace_back(road[0] - 1, road[2]);
        }
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq;
        std::vector<long long> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = appleCost[i];
            pq.emplace(i, result[i]);
        }
        while (!pq.empty()) {
            const auto [v, total] = pq.top();
            pq.pop();
            if (total > result[v])
                continue;

            for (const auto& [w, cost] : graph[v]) {
                if (result[w] > cost * (k + 1) + result[v]) {
                    result[w] = cost * (k + 1) + result[v];
                    pq.emplace(w, result[w]);
                }
            }
        }
        return result;
    }

private:
    using Pair = std::pair<int, long long>; // <v, cost>

    struct Compare {
        bool operator()(const Pair& p1, const Pair& p2) const
        {
            return p1.second > p2.second;
        }
    };
};