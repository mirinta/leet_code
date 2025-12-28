#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * There is an integer array nums that consists of n unique elements, but you have forgotten it.
 * However, you do remember every pair of adjacent elements in nums.
 *
 * You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui,
 * vi] indicates that the elements ui and vi are adjacent in nums.
 *
 * It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in
 * adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in
 * any order.
 *
 * Return the original array nums. If there are multiple solutions, return any of them.
 *
 * ! nums.length == n
 * ! adjacentPairs.length == n - 1
 * ! adjacentPairs[i].length == 2
 * ! 2 <= n <= 10^5
 * ! -10^5 <= nums[i], ui, vi <= 10^5
 * ! There exists some nums that has adjacentPairs as its pairs.
 */

class Solution {
public:
    std::vector<int> restoreArray(std::vector<std::vector<int>>& adjacentPairs)
    {
        return approach1(adjacentPairs);
    }

private:
    void dfs(std::vector<int>& result,
             std::unordered_set<int>& visited,
             int v,
             const std::unordered_map<int, std::vector<int>>& graph)
    {
        visited.insert(v);
        result.push_back(v);
        for (const auto& w : graph.at(v)) {
            if (!visited.count(w)) {
                dfs(result, visited, w, graph);
            }
        }
    }

    // DFS, time O(N), space O(N)
    std::vector<int> approach1(const std::vector<std::vector<int>>& adjacentPairs)
    {
        std::unordered_map<int, std::vector<int>> graph;
        for (const auto& pair : adjacentPairs) {
            graph[pair[0]].push_back(pair[1]);
            graph[pair[1]].push_back(pair[0]);
        }
        std::vector<int> result;
        for (const auto& [v, adjacencies] : graph) {
            if (adjacencies.size() == 1) {
                std::unordered_set<int> visited;
                dfs(result, visited, v, graph);
                return result;
            }
        }
        return {};
    }

    // topological sort, time O(N), space O(N)
    std::vector<int> approach2(const std::vector<std::vector<int>>& adjacentPairs)
    {
        std::unordered_map<int, std::vector<int>> graph;
        std::unordered_map<int, int> degrees;
        for (const auto& pair : adjacentPairs) {
            graph[pair[0]].push_back(pair[1]);
            graph[pair[1]].push_back(pair[0]);
            degrees[pair[0]]++;
            degrees[pair[1]]++;
        }
        std::queue<int> queue;
        std::unordered_set<int> visited;
        for (const auto& [v, degree] : degrees) {
            if (degree == 1) {
                queue.push(v);
                visited.insert(v);
                break;
            }
        }
        std::vector<int> result;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            result.push_back(v);
            for (const auto& w : graph[v]) {
                if (!visited.count(w) && --degrees[w] <= 1) {
                    visited.insert(w);
                    queue.push(w);
                }
            }
        }
        if (result.size() != degrees.size())
            return {};

        return result;
    }
};
