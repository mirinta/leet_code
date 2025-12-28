#include <queue>
#include <vector>

/**
 * You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1,
 * and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between
 * nodes ai and bi with weight wi.
 *
 * Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
 *
 * Your task is to modify all edges with a weight of -1 by assigning them positive integer values in
 * the range [1, 2 * 109] so that the shortest distance between the nodes source and destination
 * becomes equal to an integer target. If there are multiple modifications that make the shortest
 * distance between source and destination equal to target, any of them will be considered correct.
 *
 * Return an array containing all edges (even unmodified ones) in any order if it is possible to
 * make the shortest distance from source to destination equal to target, or an empty array if it's
 * impossible.
 *
 * Note: You are not allowed to modify the weights of edges with initial positive weights.
 *
 * ! 1 <= n <= 100
 * ! 1 <= edges.length <= n * (n - 1) / 2
 * ! edges[i].length == 3
 * ! 0 <= ai, bi < n
 * ! wi = -1 or 1 <= wi <= 10^7
 * ! ai != bi
 * ! 0 <= source, destination < n
 * ! source != destination
 * ! 1 <= target <= 10^9
 * ! The graph is connected, and there are no self-loops or repeated edges
 */

class Solution {
public:
    std::vector<std::vector<int>>
        modifiedGraphEdges(int n, std::vector<std::vector<int>>& edges, int source, int destination, int target)
    {
        std::vector<std::vector<Pair>> graph(n);
        for (const auto& e : edges) {
            if (e[2] != -1) {
                graph[e[0]].emplace_back(e[1], e[2]);
                graph[e[1]].emplace_back(e[0], e[2]);
            }
        }
        const int minDist = dijkstra(source, destination, graph);
        if (minDist < target)
            return {};

        bool match = minDist == target;
        for (auto& e : edges) {
            if (e[2] != -1)
                continue;

            e[2] = match ? 2 * 1e9 : 1;
            graph[e[0]].emplace_back(e[1], e[2]);
            graph[e[1]].emplace_back(e[0], e[2]);
            if (!match) {
                const int newMinDist = dijkstra(source, destination, graph);
                if (newMinDist <= target) {
                    e[2] += target - newMinDist;
                    match = true;
                }
            }
        }
        if (!match)
            return {};

        return edges;
    }

private:
    using Pair = std::pair<int, int>;

    int dijkstra(int src, int dst, const std::vector<std::vector<Pair>>& graph)
    {
        std::vector<int> distTo(graph.size(), INT_MAX);
        distTo[src] = 0;
        static auto compare = [](const auto& p1, const auto& p2) { return p1.second > p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> pq(compare);
        pq.emplace(src, 0);
        while (!pq.empty()) {
            const auto [v, dist] = pq.top();
            pq.pop();
            if (dist > distTo[v])
                continue;

            if (v == dst)
                return dist;

            for (const auto& [adj, w] : graph[v]) {
                if (distTo[adj] > dist + w) {
                    distTo[adj] = dist + w;
                    pq.emplace(adj, distTo[adj]);
                }
            }
        }
        return INT_MAX;
    }
};