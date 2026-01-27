#include <queue>
#include <vector>

/**
 * You are given a directed, weighted graph with n nodes labeled from 0 to n - 1, and an array edges where edges[i] =
 * [ui, vi, wi] represents a directed edge from node ui to node vi with cost wi.
 *
 * Each node ui has a switch that can be used at most once: when you arrive at ui and have not yet used its switch, you
 * may activate it on one of its incoming edges vi → ui reverse that edge to ui → vi and immediately traverse it.
 *
 * The reversal is only valid for that single move, and using a reversed edge costs 2 * wi.
 *
 * Return the minimum total cost to travel from node 0 to node n - 1. If it is not possible, return -1.
 *
 * ! 2 <= n <= 5 * 10^4
 * ! 1 <= edges.length <= 10^5
 * ! edges[i] = [ui, vi, wi]
 * ! 0 <= ui, vi <= n - 1
 * ! 1 <= wi <= 1000
 */

class Solution {
public:
    int minCost(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].emplace_back(e[1], e[2]);
            graph[e[1]].emplace_back(e[0], 2 * e[2]);
        }
        std::vector<int> distTo(n, INT_MAX);
        distTo[0] = 0;
        auto compare = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(compare)> pq(compare);
        pq.emplace(0, 0);
        while (!pq.empty()) {
            const auto [cost, v] = pq.top();
            pq.pop();
            if (v == n - 1)
                return cost;

            if (cost > distTo[v])
                continue;

            for (const auto& [next, w] : graph[v]) {
                if (distTo[v] + w < distTo[next]) {
                    distTo[next] = distTo[v] + w;
                    pq.emplace(distTo[next], next);
                }
            }
        }
        return -1;
    }
};