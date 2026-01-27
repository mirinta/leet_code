#include <queue>

#include "definition.h"

/**
 * @brief Calculate the weight of the shortest path from src to dst using the Dijkstra's algorithm.
 *
 * @note The given graph must not have negative edge weights.
 *
 * @note Return LLONG_MAX if it is not reachable from src to dst.
 *
 * @note Time Complexity = O(V + ElogV), Space Complexity = O(V), where E and V are the number of
 * vertices and edges, respectively.
 */
long long dijkstra(int src, int dst, const Graph& graph)
{
    const int n = graph.size();
    std::vector<long long> distTo(n, LLONG_MAX);
    distTo[src] = 0;
    using Pair = std::pair<int, long long>; // <vertex v, weights from src to v>
    auto comparator = [](const Pair& p1, const Pair& p2) { return p1.second > p2.second; };
    std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator); // min heap;
    pq.emplace(0, src);
    while (!pq.empty()) {
        const auto [v, weights] = pq.top();
        pq.pop();
        if (v == dst)
            return weights;

        if (weights > distTo[v])
            continue;

        for (const auto& [adj, weight] : graph[v]) {
            if (distTo[v] + weight < distTo[adj]) {
                distTo[adj] = distTo[v] + weight;
                pq.emplace(adj, distTo[adj]);
            }
        }
    }
    return LLONG_MAX;
}