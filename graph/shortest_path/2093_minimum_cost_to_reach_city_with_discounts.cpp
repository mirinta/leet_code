#include <array>
#include <climits>
#include <queue>
#include <vector>

/**
 * A series of highways connect n cities numbered from 0 to n - 1. You are given a 2D integer array
 * highways where highways[i] = [city1i, city2i, tolli] indicates that there is a highway that
 * connects city1i and city2i, allowing a car to go from city1i to city2i and vice versa for a cost
 * of tolli.
 *
 * You are also given an integer discounts which represents the number of discounts you have. You
 * can use a discount to travel across the ith highway for a cost of tolli / 2 (integer division).
 * Each discount may only be used once, and you can only use at most one discount per highway.
 *
 * Return the minimum total cost to go from city 0 to city n - 1, or -1 if it is not possible to go
 * from city 0 to city n - 1.
 *
 * ! 2 <= n <= 1000
 * ! 1 <= highways.length <= 1000
 * ! highways[i].length == 3
 * ! 0 <= city1i, city2i <= n - 1
 * ! city1i != city2i
 * ! 0 <= tolli <= 10^5
 * ! 0 <= discounts <= 500
 * ! There are no duplicate highways.
 */

class Solution {
public:
    int minimumCost(int n, std::vector<std::vector<int>>& highways, int discounts)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& path : highways) {
            graph[path[0]].emplace_back(path[1], path[2]);
            graph[path[1]].emplace_back(path[0], path[2]);
        }
        // costTo[v][r] = min cost from vertex 0 to vertex v with r remaining discounts
        std::vector<std::vector<int>> costTo(n, std::vector<int>(1 + discounts, INT_MAX));
        costTo[0][discounts] = 0;
        std::priority_queue<Triplet, std::vector<Triplet>, Compare> pq;
        pq.push({0, 0, discounts});
        while (!pq.empty()) {
            const auto [costToV, v, remainingDiscounts] = pq.top();
            pq.pop();
            if (costToV > costTo[v][remainingDiscounts])
                continue;

            if (v == n - 1)
                return costToV;

            for (const auto& [w, cost] : graph[v]) {
                // case 1: go to vertex w using a discount
                if (remainingDiscounts > 0 && costToV + cost / 2 < costTo[w][remainingDiscounts - 1]) {
                    costTo[w][remainingDiscounts - 1] = costToV + cost / 2;
                    pq.push({costTo[w][remainingDiscounts - 1], w, remainingDiscounts - 1});
                }
                // case 2: go to vertex w without using a discount
                if (costToV + cost < costTo[w][remainingDiscounts]) {
                    costTo[w][remainingDiscounts] = costToV + cost;
                    pq.push({costTo[w][remainingDiscounts], w, remainingDiscounts});
                }
            }
        }
        return -1;
    }

private:
    using Triplet = std::array<int, 3>; // <cost to v, v, remaining discounts>

    struct Compare {
        bool operator()(const Triplet& t1, const Triplet& t2) const
        {
            return t1[0] > t2[0];
        }
    };
};
