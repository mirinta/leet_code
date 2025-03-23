#include <queue>
#include <vector>

/**
 * You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional
 * roads between some intersections. The inputs are generated such that you can reach any
 * intersection from any other intersection and that there is at most one road between any two
 * intersections.
 *
 * You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means
 * that there is a road between intersections ui and vi that takes timei minutes to travel. You want
 * to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest
 * amount of time.
 *
 * Return the number of ways you can arrive at your destination in the shortest amount of time.
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 200
 * ! n - 1 <= roads.length <= n * (n - 1) / 2
 * ! roads[i].length == 3
 * ! 0 <= ui, vi <= n - 1
 * ! 1 <= timei <= 10^9
 * ! ui != vi
 * ! There is at most one road connecting any two intersections.
 * ! You can reach any intersection from any other intersection.
 */

class Solution
{
public:
    int countPaths(int n, std::vector<std::vector<int>>& roads)
    {
        static constexpr int kMod = 1e9 + 7;
        std::vector<std::vector<Pair>> graph(n);
        for (const auto& r : roads) {
            graph[r[0]].emplace_back(r[1], r[2]);
            graph[r[1]].emplace_back(r[0], r[2]);
        }
        std::vector<long long> distTo(n, LLONG_MAX);
        distTo[0] = 0;
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq;
        pq.emplace(0, 0);
        std::vector<int> count(n, 0);
        count[0] = 1;
        while (!pq.empty()) {
            const auto [v, dist] = pq.top();
            pq.pop();
            if (dist > distTo[v])
                continue;

            for (const auto& [adj, weight] : graph[v]) {
                if (distTo[adj] > dist + weight) {
                    distTo[adj] = dist + weight;
                    count[adj] = count[v];
                    pq.emplace(adj, distTo[adj]);
                } else if (distTo[adj] == dist + weight) {
                    count[adj] = (count[adj] + count[v]) % kMod;
                }
            }
        }
        return count[n - 1];
    }

private:
    using Pair = std::pair<int, long long>;

    struct Compare
    {
        bool operator()(const Pair& p1, const Pair& p2) const { return p1.second > p2.second; }
    };
};
