#include <queue>
#include <vector>

/**
 * There are a total of "numCourses" courses you have to take, labeled from 0 to numCourse - 1. You
 * are given an array "prerequisites" where prerequisites[i] = [ai, bi] indicates that you must take
 * course bi first if you want to take course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 *
 * Return true if you can finish all courses. Otherwise, return false.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 * Explanation: There are a total of 2 courses to take. To take course 1 you should have finished
 * course 0. So it is possible.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0, and to take course 0 you should also have
 * finished course 1. So it is impossible.
 *
 * ! 1 <= numCourses <= 2000
 * ! 0 <= prerequisites.length <= 5000
 * ! prerequisites[i].length == 2
 * ! 0 <= ai, bi < numCourses
 * ! All the pairs prerequisites[i] are unique.
 */

class Solution {
public:
    bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> graph(numCourses);
        for (const auto& prerequisite : prerequisites) {
            graph[prerequisite[1]].push_back(prerequisite[0]);
        }
        return approach2(graph);
    }

private:
    // Kahn's algorithm (topological sorting), time O(V+E), space O(V+E)
    // - V is the number of vertices (courses),
    // - E is the number of edges (prerequisites)
    bool approach2(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<int> indegrees(n, 0);
        for (int i = 0; i < n; ++i) {
            for (const auto& v : graph[i]) {
                indegrees[v]++;
            }
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        int count = 0;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            count++;
            for (const auto& adj : graph[v]) {
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        return count == n;
    }

    // DFS, time O(V+E), space O(V+E)
    // - V is the number of vertices (courses),
    // - E is the number of edges (prerequisites)
    // white = not processed
    // gray = being processed
    // black = process finished
    enum Color { White, Gray, Black };
    bool approach1(const std::vector<std::vector<int>>& graph)
    {
        const int n = graph.size();
        std::vector<Color> colors(n, White);
        for (int i = 0; i < n; ++i) {
            if (colors[i] == White && hasCycle(colors, i, graph))
                return false;
        }
        return true;
    }

    bool hasCycle(std::vector<Color>& colors, int v, const std::vector<std::vector<int>>& graph)
    {
        colors[v] = Gray;
        for (const auto& adj : graph[v]) {
            if (colors[adj] == Gray)
                return true;

            if (colors[adj] == White && hasCycle(colors, adj, graph))
                return true;
        }
        colors[v] = Black;
        return false;
    }
};
