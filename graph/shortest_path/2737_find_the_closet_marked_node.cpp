#include <queue>
#include <unordered_set>
#include <vector>

/**
 * You are given a positive integer n which is the number of nodes of a 0-indexed directed weighted
 * graph and a 0-indexed 2D array edges where edges[i] = [ui, vi, wi] indicates that there is an
 * edge from node ui to node vi with weight wi.
 *
 * You are also given a node s and a node array marked; your task is to find the minimum distance
 * from s to any of the nodes in marked.
 *
 * Return an integer denoting the minimum distance from s to any node in marked or -1 if there are
 * no paths from s to any of the marked nodes.
 *
 * ! 2 <= n <= 500
 * ! 1 <= edges.length <= 10^4
 * ! edges[i].length = 3
 * ! 0 <= edges[i][0], edges[i][1] <= n - 1
 * ! 1 <= edges[i][2] <= 10^6
 * ! 1 <= marked.length <= n - 1
 * ! 0 <= s, marked[i] <= n - 1
 * ! s != marked[i]
 * ! marked[i] != marked[j] for every i != j
 * ! The graph might have repeated edges.
 * ! The graph is generated such that it has no self-loops.
 */

class Solution {
public:
    int minimumDistance(int n, std::vector<std::vector<int>>& edges, int s, std::vector<int>& marked)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].emplace_back(e[1], e[2]);
        }
        std::unordered_set<int> set(marked.begin(), marked.end());
        std::vector<int> distTo(n, INT_MAX);
        distTo[s] = 0;
        using Pair = std::pair<int, int>;
        auto compare = [](const Pair& p1, const Pair& p2) { return p1.second > p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> pq(compare);
        pq.emplace(s, 0);
        while (!pq.empty()) {
            const auto [v, dist] = pq.top();
            pq.pop();
            if (dist > distTo[v])
                continue;

            if (set.count(v))
                return dist;

            for (const auto& [adj, weight] : graph[v]) {
                if (distTo[adj] > dist + weight) {
                    distTo[adj] = dist + weight;
                    pq.emplace(adj, distTo[adj]);
                }
            }
        }
        return -1;
    }
};