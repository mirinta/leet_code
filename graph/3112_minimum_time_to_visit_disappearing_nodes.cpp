#include <queue>
#include <vector>

/**
 * There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui,
 * vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi
 * units.
 *
 * Additionally, you are given an array disappear, where disappear[i] denotes the time when the node
 * i disappears from the graph and you won't be able to visit it.
 *
 * Notice that the graph might be disconnected and might contain multiple edges.
 *
 * Return the array answer, with answer[i] denoting the minimum units of time required to reach node
 * i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
 *
 * ! 1 <= n <= 5 * 10^4
 * ! 0 <= edges.length <= 10^5
 * ! edges[i] == [ui, vi, lengthi]
 * ! 0 <= ui, vi <= n - 1
 * ! 1 <= lengthi <= 10^5
 * ! disappear.length == n
 * ! 1 <= disappear[i] <= 10^5
 */

class Solution {
public:
    std::vector<int> minimumTime(int n, std::vector<std::vector<int>>& edges, std::vector<int>& disappear)
    {
        using Pair = std::pair<int, int>;
        std::vector<std::vector<Pair>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        std::vector<int> minTimeTo(n, INT_MAX);
        minTimeTo[0] = 0;
        auto comparator = [](const auto& p1, const auto& p2) { return p1.second > p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        pq.emplace(0, 0);
        while (!pq.empty()) {
            const auto [v, time] = pq.top();
            pq.pop();
            if (time > minTimeTo[v])
                continue;

            for (const auto& [w, t] : graph[v]) {
                if (time + t < disappear[w] && time + t < minTimeTo[w]) {
                    pq.emplace(w, time + t);
                    minTimeTo[w] = time + t;
                }
            }
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = minTimeTo[i] == INT_MAX ? -1 : minTimeTo[i];
        }
        return result;
    }
};