#include <queue>
#include <vector>

/**
 * You are maintaining a project that has n methods numbered from 0 to n - 1.
 *
 * You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates
 * that method ai invokes method bi.
 *
 * There is a known but in method k. Method k, along with any method invoked by it, either directly or indirectly, are
 * considered suspicious and we aim to remove them.
 *
 * A group of methods can only be removed if no method outside the group invokes any method within it.
 *
 * Return an array containing all the remaining methods after removing all the suspicious methods. You may return the
 * answer in any order. If it is not possible to remove all the suspicious methods, none should be removed.
 *
 * ! 1 <= n <= 10^5
 * ! 0 <= k <= n - 1
 * ! 0 <= invocations.length <= 2 * 10^5
 * ! invocations[i] == [ai, bi]
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 * ! invocations[i] != invocations[j]
 */

class Solution {
public:
    std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations)
    {
        std::vector<int> indegrees(n, 0);
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : invocations) {
            graph[edge[0]].emplace_back(edge[1]);
            indegrees[edge[1]]++;
        }
        std::vector<bool> visited(n, false);
        std::queue<int> queue;
        queue.emplace(k);
        visited[k] = true;
        while (!queue.empty()) {
            for (int sz = queue.size(); sz > 0; --sz) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& next : graph[v]) {
                    indegrees[next] = std::max(0, indegrees[next] - 1);
                    if (!visited[next]) {
                        visited[next] = true;
                        queue.emplace(next);
                    }
                }
            }
        }
        bool canRemove = true;
        for (int i = 0; i < n; ++i) {
            if (visited[i] && indegrees[i] != 0) {
                canRemove = false;
                break;
            }
        }
        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (visited[i] && canRemove)
                continue;

            result.emplace_back(i);
        }
        return result;
    }
};