#include <queue>
#include <tuple>
#include <vector>

/**
 * You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph
 * consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that
 * there is an edge between nodes ai and bi with weight wi.
 *
 * Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a
 * boolean array answer where answer[i] is true if the edge edges[i] is part of at least one
 * shortest path. Otherwise, answer[i] is false.
 *
 * Return the array answer.
 *
 * Note that the graph may not be connected.
 *
 * ! 2 <= n <= 5 * 10^4
 * ! m == edges.length
 * ! 1 <= m <= min(5 * 10^4, n * (n - 1) / 2)
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! 1 <= wi <= 10^5
 * ! There are no repeated edges.
 */

class Solution {
public:
    std::vector<bool> findAnswer(int n, std::vector<std::vector<int>>& edges)
    {
        using Tuple = std::tuple<int, int, int>; // <vertex, weight, edgeID>
        using Pair = std::pair<int, int>;        // <dist, vertex>
        std::vector<std::vector<Tuple>> graph(n);
        for (int i = 0; i < edges.size(); ++i) {
            graph[edges[i][0]].emplace_back(edges[i][1], edges[i][2], i);
            graph[edges[i][1]].emplace_back(edges[i][0], edges[i][2], i);
        }
        std::vector<int> distTo(n, INT_MAX);
        distTo[0] = 0;
        auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        pq.emplace(0, 0);
        while (!pq.empty()) {
            const auto [dist, v] = pq.top();
            pq.pop();
            if (dist > distTo[v])
                continue;

            for (const auto& [adj, weight, id] : graph[v]) {
                if (distTo[adj] > distTo[v] + weight) {
                    distTo[adj] = distTo[v] + weight;
                    pq.emplace(distTo[adj], adj);
                }
            }
        }
        std::vector<bool> result(edges.size(), false);
        std::queue<int> queue;
        queue.push(n - 1);
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            if (distTo[v] == INT_MAX)
                continue;

            for (const auto& [adj, weight, id] : graph[v]) {
                if (distTo[adj] != INT_MAX && distTo[v] == distTo[adj] + weight) {
                    result[id] = true;
                    queue.push(adj);
                }
            }
        }
        return result;
    }
};