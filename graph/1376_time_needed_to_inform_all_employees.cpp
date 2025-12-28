#include <queue>
#include <vector>

/**
 * A company has "n" employees with a unique ID for each employee from 0 to n - 1. The head of the
 * company is the one with "headID".
 *
 * Each employee has one direct manager given in the manager array where manager[i] is the direct
 * manager of the ith employee, manager[headID] = -1. Also, it is guaranteed that the subordination
 * relationships have a tree structure.
 *
 * The head of the company wants to inform all the company employees of an urgent piece of news. He
 * will inform his direct subordinates, and they will inform there subordinates, and so on until all
 * employees know about the urgent news.
 *
 * The ith employee needs informTime[i] minutes to inform all of this direct subordinates (i.e.,
 * After informTime[i] minutes, all his direct subordinates can start spreading the news).
 *
 * Return the number of minutes needed to inform all the employees about the urgent news.
 *
 * ! 1 <= n <= 10^5
 * ! 0 <= headID < n
 * ! manager.length == n
 * ! 0 <= manager[i] < n
 * ! manager[headID] == -1
 * ! informTime.length == n
 * ! 0 <= informTime[i] <= 1000
 * ! informTime[i] == 0 if employee i has no subordinates.
 * ! It is guaranteed that all the employees can be informed.
 */

class Solution {
public:
    int numOfMinutes(int n, int headID, std::vector<int>& manager, std::vector<int>& informTime)
    {
        // it is a tree structure, so we don't need a "visited" array
        return approach2(n, headID, manager, informTime);
    }

private:
    // DFS, time O(N), space O(N)
    int approach2(int n, int headID, std::vector<int>& manager, std::vector<int>& informTime)
    {
        std::vector<std::vector<int>> graph(n);
        for (int i = 0; i < manager.size(); ++i) {
            if (manager[i] != -1) {
                graph[manager[i]].push_back(i);
            }
        }
        return dfs(headID, informTime, graph);
    }

    int dfs(int current, const std::vector<int>& informTime, const std::vector<std::vector<int>>& graph)
    {
        int result = 0;
        for (const auto& adj : graph[current]) {
            result = std::max(result, informTime[current] + dfs(adj, informTime, graph));
        }
        return result;
    }

    // BFS, time O(N), space O(N)
    int approach1(int n, int headID, std::vector<int>& manager, std::vector<int>& informTime)
    {
        std::vector<std::vector<int>> graph(n);
        for (int i = 0; i < manager.size(); ++i) {
            if (manager[i] != -1) {
                graph[manager[i]].push_back(i);
            }
        }
        std::queue<std::pair<int, int>> queue; // <vertex, distance>
        queue.emplace(headID, 0);
        int result = 0;
        while (!queue.empty()) {
            const auto [v, time] = queue.front();
            queue.pop();
            result = std::max(result, time);
            for (const auto& adj : graph[v]) {
                queue.emplace(adj, time + informTime[v]);
            }
        }
        return result;
    }
};
