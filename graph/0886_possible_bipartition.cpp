#include <queue>
#include <vector>

/**
 * We want to split a group of "n" people (labeled from 1 to n) into groups of any size. Each person
 * may dislike some other people, and they should not go into the same group.
 *
 * Given the integer "n" and the array "dislikes" where dislike[i] = [ai, bi] indicates that the
 * person labeled ai does not like the person labeled bi, return true if it is possible to split
 * everyone into two groups in this way.
 *
 * ! 1 <= n <= 2000
 * ! 0 <= dislikes.length <= 10^4
 * ! dislikes[i].length == 2
 * ! 1 <= ai < bi <= n
 * ! All the pairs of dislikes are unique.
 */

class Solution {
public:
    bool possibleBipartition(int n, std::vector<std::vector<int>>& dislikes)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& dislike : dislikes) {
            graph[dislike[0] - 1].push_back(dislike[1] - 1);
            graph[dislike[1] - 1].push_back(dislike[0] - 1);
        }
        return approach2(graph);
    }

private:
    // BFS: time O(V+E), space O(V+E)
    bool approach2(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<int> colors(n, 0); // 0 or not visited, -1 for blue, 1 for red
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (colors[i] != 0)
                continue;

            queue.push(i);
            colors[i] = 1;
            while (!queue.empty()) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& adj : graph[v]) {
                    if (colors[adj] == 0) {
                        colors[adj] = -colors[v];
                        queue.push(adj);
                    } else if (colors[adj] == colors[v])
                        return false;
                }
            }
        }
        return true;
    }

    // DFS, time O(V+E), space O(V+E)
    bool approach1(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<int> colors(n, 0); // 0 or not visited, -1 for blue, 1 for red
        for (int i = 0; i < n; ++i) {
            if (colors[i] != 0)
                continue;

            colors[i] = 1;
            if (!dfs(colors, i, graph))
                return false;
        }
        return true;
    }

    bool dfs(std::vector<int>& colors, int v, const std::vector<std::vector<int>>& graph)
    {
        for (const auto& adj : graph[v]) {
            if (colors[adj] == 0) {
                colors[adj] = -colors[v];
                if (!dfs(colors, adj, graph))
                    return false;

            } else if (colors[adj] == colors[v])
                return false;
        }
        return true;
    }
};
