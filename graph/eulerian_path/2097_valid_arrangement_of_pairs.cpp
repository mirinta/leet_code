#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement
 * of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
 *
 * Return any valid arrangement of pairs.
 *
 * Note: The inputs will be generated such that there exists a valid arrangement of pairs.
 *
 * ! 1 <= pairs.length <= 10^5
 * ! pairs[i].length == 2
 * ! 0 <= starti, endi <= 10^9
 * ! starti != endi
 * ! No two pairs are exactly the same.
 * ! There exists a valid arrangement of pairs.
 */

class Solution {
public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>>& pairs)
    {
        std::unordered_map<int, int> indegree;
        std::unordered_map<int, int> outdegree;
        std::unordered_map<int, std::vector<int>> graph;
        for (const auto& p : pairs) {
            const int from = p[0];
            const int to = p[1];
            indegree[to]++;
            outdegree[from]++;
            graph[from].push_back(to);
        }
        // the existence of eulerian path is guaranteed
        int start = graph.begin()->first;
        for (const auto& [v, _] : graph) {
            if (outdegree[v] - indegree[v] == 1) {
                start = v;
                break;
            }
        }
        std::vector<int> path;
        dfs(path, graph, start);
        std::reverse(path.begin(), path.end());
        std::vector<std::vector<int>> result;
        for (int i = 0; i + 1 < path.size(); ++i) {
            result.push_back({path[i], path[i + 1]});
        }
        return result;
    }

private:
    void dfs(std::vector<int>& path, std::unordered_map<int, std::vector<int>>& graph, int start)
    {
        while (!graph[start].empty()) {
            const int next = graph[start].back();
            graph[start].pop_back();
            dfs(path, graph, next);
        }
        path.push_back(start);
    }
};