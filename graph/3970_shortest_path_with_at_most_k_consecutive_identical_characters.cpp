#include <climits>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

/**
 * You are given an integer n representing the number of nodes in a directed weighted graph, numbered from 0 to n - 1.
 * This is represented by a 2D integer array edges, where edges[i] = [ui, vi, wi] represents a directed edge from node
 * ui to node vi with weight wi.
 *
 * You are also given a string labels of length n, where labels[i] is the character assigned to node i, and an integer
 * k.
 *
 * Return the minimum total edge weight of a path from node 0 to node n - 1 such that the concatenation of the labels of
 * the nodes along the path contains at most k consecutive identical characters. If no valid path exists, return -1.
 *
 * ! 1 <= n == labels.length <= 5 * 10^4
 * ! 0 <= edges.length <= 5 * 10^4
 * ! edges[i] == [ui, vi, wi]
 * ! 0 <= ui, vi <= n - 1
 * ! ui != vi
 * ! 1 <= wi <= 10^4
 * ! labels consists of lowercase English letters
 * ! 1 <= k <= 50
 */

class Solution {
public:
    int shortestPath(int n, std::vector<std::vector<int>>& edges, std::string labels, int k)
    {
        std::vector<std::vector<std::pair<int, long long>>> graph(n); // graph[from][i] = {to, weight}
        for (const auto& e : edges) {
            graph[e[0]].emplace_back(e[1], e[2]);
        }
        std::vector<std::vector<long long>> distTo(n, std::vector<long long>(k + 1, LLONG_MAX));
        distTo[0][1] = 0;
        using Tuple = std::tuple<long long, int, int>; // <dist, node, num of consecutive labels[node]>
        auto compare = [](const Tuple& t1, const Tuple& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(compare)> pq(compare);
        pq.emplace(0, 0, 1);
        while (!pq.empty()) {
            const auto [dist, node, count] = pq.top();
            pq.pop();
            if (dist > distTo[node][count])
                continue;

            if (node == n - 1)
                return dist;

            for (const auto& [next, weight] : graph[node]) {
                const int newCount = labels[node] == labels[next] ? count + 1 : 1;
                if (newCount > k)
                    continue;

                if (const int newDist = dist + weight; newDist < distTo[next][newCount]) {
                    distTo[next][newCount] = newDist;
                    pq.emplace(newDist, next, newCount);
                }
            }
        }
        return -1;
    }
};
