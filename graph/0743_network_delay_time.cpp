#include <climits>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given a network of "n" nodes, labeled from 1 to n. You are also given "times", a list of
 * travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the
 * target node, and wi is the time it takes for a signal to travel from source to target.
 *
 * We will send a signal from a given node "k". Return the minimum time it takes for all the "n"
 * nodes to receive the signal. If it is impossible for all the "n" nodes to receive the signal,
 * return -1.
 *
 * ! 1 <= k <= n
 * ! 1 <= ui, vi <= n
 * ! ui != vi
 * ! 0 <= wi
 * ! All the paris (ui, vi) are unique. (i.e., no multiple edges)
 */

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k)
    {
        // shortest path, Dijkstra's algorithm
        // #NOTICE# nodes are 1-indexed
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
        for (const auto& time : times) {
            graph[time[0] - 1].emplace_back(time[2], time[1] - 1);
        }
        const int source = k - 1;
        auto comp = [](const auto& p1, const auto& p2) -> bool { return p1.first > p2.first; };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> pq(comp);
        pq.emplace(0, source);
        std::vector<int> distTo(n, INT_MAX); // distTo[i] = distance between source and i
        distTo[source] = 0;
        while (!pq.empty()) {
            const auto [dist, v] = pq.top();
            pq.pop();
            if (dist > distTo[v])
                continue;

            for (const auto& [weight, w] : graph[v]) {
                if (distTo[w] > weight + distTo[v]) {
                    distTo[w] = weight + distTo[v];
                    pq.emplace(distTo[w], w);
                }
            }
        }
        const int maxTime = *std::max_element(distTo.begin(), distTo.end());
        return maxTime == INT_MAX ? -1 : maxTime;
    }
};