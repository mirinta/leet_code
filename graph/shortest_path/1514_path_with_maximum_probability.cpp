#include <queue>
#include <vector>

/**
 * You are given an undirected weighted graph of "n" nodes (0-indexed), represented by an edge list
 * where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of
 * success of traversing that edge succProb[i].
 *
 * Given two nodes start and end, find the path with the maximum probability of success to go from
 * start to end and return its success probability.
 *
 * It there is no path from start to end, return 0. Your answer will be accepted if it differs from
 * the correct answer by at mode 1e-5.
 *
 * ! 2 <= n <= 10^4
 * ! 0 <= start, end < n
 * ! start != end
 * ! 0 <= a, b < n
 * ! a != b
 * ! 0 <= succProb.length == edges.length <= 2*10^4
 * ! 0 <= succProb[i] <= 1
 * ! There is at most one edge between every two nodes.
 */

class Solution {
public:
    double maxProbability(int n,
                          std::vector<std::vector<int>>& edges,
                          std::vector<double>& succProb,
                          int start_node,
                          int end_node)
    {
        return approach2(n, edges, succProb, start_node, end_node);
    }

private:
    // Bellman-Ford
    double approach2(int n,
                     const std::vector<std::vector<int>>& edges,
                     const std::vector<double>& succProb,
                     int start_node,
                     int end_node)
    {
        std::vector<double> dp(n, 0);
        dp[start_node] = 1;
        for (int i = 1; i < n; ++i) {
            bool update = false;
            for (int j = 0; j < edges.size(); ++j) {
                const auto& prob = succProb[j];
                const auto& a = edges[j][0];
                const auto& b = edges[j][1];
                if (dp[a] * prob > dp[b]) {
                    dp[b] = dp[a] * prob;
                    update = true;
                }
                if (dp[b] * prob > dp[a]) {
                    dp[a] = dp[b] * prob;
                    update = true;
                }
            }
            if (!update)
                break;
        }
        return dp[end_node];
    }

    // Dijkstra
    double approach1(int n,
                     const std::vector<std::vector<int>>& edges,
                     const std::vector<double>& succProb,
                     int start_node,
                     int end_node)
    {
        std::vector<std::vector<std::pair<int, double>>> graph(n);
        for (int i = 0; i < edges.size(); ++i) {
            graph[edges[i][0]].emplace_back(edges[i][1], succProb[i]);
            graph[edges[i][1]].emplace_back(edges[i][0], succProb[i]);
        }
        using Pair = std::pair<int, double>;
        auto compare = [](const auto& p1, const auto& p2) { return p1.second < p2.second; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> pq(compare);
        pq.emplace(start_node, 1);
        std::vector<double> probTo(n);
        probTo[start_node] = 1;
        while (!pq.empty()) {
            const auto [node, prob] = pq.top();
            pq.pop();
            if (prob < probTo[node])
                continue;

            if (node == end_node)
                return prob;

            for (const auto& [next, p] : graph[node]) {
                if (probTo[next] < probTo[node] * p) {
                    probTo[next] = probTo[node] * p;
                    pq.emplace(next, probTo[next]);
                }
            }
        }
        return 0;
    }
};
