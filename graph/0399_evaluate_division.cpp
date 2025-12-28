#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given array of variable pairs "equations" and an array of real numbers "values", where
 * equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi
 * is a string that represents a single variable.
 *
 * You are also given some "queries", where queries[j] = [Cj, Dj] represents jth query where you
 * must find the answer for Cj / Dj = ?
 *
 * Return the answers to all queries. If a single answer cannot be determined, return -1.0.
 *
 * Note: The input is always valid. You may assume that evaluating the queries will not result in
 * division by zero and that there is no contradiction.
 *
 * ! 1 <= equations.length <= 20
 * ! equations[i].length == 2
 * ! 1 <= Ai.length, Bi.length <= 5
 * ! values.length == equations.length
 * ! 0.0 < values[i] <= 20.0
 * ! 1 <= queries.length <= 20
 * ! queries[i].length == 2
 * ! 1 <= Cj.length, Dj.length <= 5
 * ! Ai, Bi, Cj, Dj consist of lower case English letters and digits.
 */

class Solution {
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations,
                                     std::vector<double>& values,
                                     std::vector<std::vector<std::string>>& queries)
    {
        Graph graph;
        for (int i = 0; i < equations.size(); ++i) {
            const auto& dividend = equations[i][0];
            const auto& divisor = equations[i][1];
            graph[dividend][divisor] = values[i];
            graph[divisor][dividend] = 1 / values[i];
        }
        std::unordered_set<std::string> visited;
        std::vector<double> result;
        for (const auto& query : queries) {
            const auto& dividend = query[0];
            const auto& divisor = query[1];
            if (!graph.count(dividend) || !graph.count(divisor)) {
                result.push_back(-1);
            } else if (dividend == divisor) {
                result.push_back(1);
            } else {
                visited.clear();
                result.push_back(dfs(visited, dividend, divisor, 1.0, graph));
            }
        }
        return result;
    }

private:
    using Graph = std::unordered_map<std::string, std::unordered_map<std::string, double>>;

    double dfs(std::unordered_set<std::string>& visited,
               const std::string& start,
               const std::string& target,
               double product,
               const Graph& graph)
    {
        if (start == target)
            return product;

        visited.insert(start);
        double result = -1;
        for (const auto& [adj, val] : graph.at(start)) {
            if (visited.count(adj))
                continue;

            result = dfs(visited, adj, target, product * val, graph);
            if (result != -1)
                break;
        }
        return result;
    }
};
