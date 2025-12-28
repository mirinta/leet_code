#include <queue>
#include <vector>

/**
 * You are given an integer n and a 2D integer array queries.
 *
 * There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city
 * i to city i + 1 for all 0 <= i < n - 1.
 *
 * queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city
 * vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
 *
 * Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the
 * length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
 *
 * ! 3 <= n <= 500
 * ! 1 <= queries.length <= 500
 * ! queries[i].length == 2
 * ! 0 <= queries[i][0] < queries[i][1] < n
 * ! 1 < queries[i][1] - queries[i][0]
 * ! There are no repeated roads among the queries.
 */

class Solution {
public:
    std::vector<int> shortestDistanceAfterQueries(int n, std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<int>> graph(n);
        for (int i = 0; i < n - 1; ++i) {
            graph[i].push_back(i + 1);
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            graph[query[0]].push_back(query[1]);
            result.push_back(solve(graph));
        }
        return result;
    }

private:
    int solve(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        int steps = 0;
        std::queue<int> queue;
        queue.emplace(0);
        std::vector<bool> visited(n, false);
        visited[0] = true;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& w : graph[v]) {
                    if (visited[w])
                        continue;

                    if (w == n - 1)
                        return steps + 1;

                    visited[w] = true;
                    queue.emplace(w);
                }
            }
            steps++;
        }
        return -1;
    }
};