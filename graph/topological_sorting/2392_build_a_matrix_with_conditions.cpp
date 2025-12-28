#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given a positive integer k. You are also given:
 *
 * - a 2D integer array rowConditions of size n where rowConditions[i] = [abovei, belowi], and
 *
 * - a 2D integer array colConditions of size m where colConditions[i] = [lefti, righti].
 *
 * The two arrays contain integers from 1 to k.
 *
 * You have to build a k x k matrix that contains each of the numbers from 1 to k exactly once. The
 * remaining cells should have the value 0.
 *
 * The matrix should also satisfy the following conditions:
 *
 * - The number abovei should appear in a row that is strictly above the row at which the number
 * belowi appears for all i from 0 to n - 1.
 *
 * - The number lefti should appear in a column that is strictly left of the column at which the
 * number righti appears for all i from 0 to m - 1.
 *
 * Return any matrix that satisfies the conditions. If no answer exists, return an empty matrix.
 *
 * ! 2 <= k <= 400
 * ! 1 <= rowConditions.length, colConditions.length <= 10^4
 * ! rowConditions[i].length == colConditions[i].length == 2
 * ! 1 <= abovei, belowi, lefti, righti <= k
 * ! abovei != belowi
 * ! lefti != righti
 */

class Solution {
public:
    std::vector<std::vector<int>>
        buildMatrix(int k, std::vector<std::vector<int>>& rowConditions, std::vector<std::vector<int>>& colConditions)
    {
        std::vector<std::vector<int>> result(k, std::vector<int>(k, 0));
        const auto row = topologicalSort(k, rowConditions);
        if (row.empty())
            return {};

        const auto col = topologicalSort(k, colConditions);
        if (col.empty())
            return {};

        for (int val = 1; val <= k; ++val) {
            result[row.at(val)][col.at(val)] = val;
        }
        return result;
    }

private:
    std::unordered_map<int, int> topologicalSort(int n, const std::vector<std::vector<int>>& conditions)
    {
        std::vector<std::vector<int>> graph(n + 1); // 1-indexed
        std::vector<int> indegrees(n + 1, 0);       // 1-indexed
        for (const auto& condition : conditions) {
            graph[condition[0]].push_back(condition[1]);
            indegrees[condition[1]]++;
        }
        std::queue<int> queue;
        for (int i = 1; i <= n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::unordered_map<int, int> result; // value to index
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            result[v] = result.size();
            for (const auto& w : graph[v]) {
                if (--indegrees[w] == 0) {
                    queue.push(w);
                }
            }
        }
        if (result.size() != n)
            return {}; // there is a cycle

        return result;
    }
};