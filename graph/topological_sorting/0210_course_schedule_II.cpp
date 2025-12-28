#include <queue>
#include <vector>

/**
 * There are a total of "numCourses" courses you have to take, labeled from 0 to numCourse - 1. You
 * are given an array "prerequisites" where prerequisites[i] = [ai, bi] indicates that you must take
 * course bi first if you want to take course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
 *
 * Return the ordering of courses you should take to finish all courses. If there are many valid
 * answers, return any of them. If it is impossible to finish all courses, return an empty array.
 *
 * ! 1 <= numCourses <= 2000
 * ! 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * ! prerequisites[i].length == 2
 * ! 0 <= ai, bi < numCourses
 * ! ai != bi
 * ! All the pairs [ai, bi] are distinct.
 */

class Solution {
public:
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        return approach2(numCourses, prerequisites);
    }

private:
    // Kahn's algorithm, time O(V+E), space O(V+E)
    std::vector<int> approach2(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> graph(numCourses);
        std::vector<int> indegrees(numCourses, 0);
        for (const auto& prerequisite : prerequisites) {
            graph[prerequisite[1]].push_back(prerequisite[0]);
            indegrees[prerequisite[0]]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<int> result;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            result.push_back(v);
            for (const auto& adj : graph[v]) {
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        if (result.size() != numCourses)
            return {};

        return result;
    }

    // DFS, time O(V+E), space O(V+E)
    // White: not processed
    // Gray: being processed
    // Black: process finished
    enum Color { White, Gray, Black };

    std::vector<int> approach1(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> graph(numCourses);
        for (const auto& prerequisite : prerequisites) {
            graph[prerequisite[1]].push_back(prerequisite[0]);
        }
        std::vector<Color> colors(numCourses, White);
        std::vector<int> result;
        for (int i = 0; i < numCourses; ++i) {
            if (colors[i] == White && hasCycle(colors, result, i, graph))
                return {};
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    bool hasCycle(std::vector<Color>& colors,
                  std::vector<int>& result,
                  int v,
                  const std::vector<std::vector<int>>& graph)
    {
        colors[v] = Gray;
        for (const auto& adj : graph[v]) {
            if (colors[adj] == Gray)
                return true;

            if (colors[adj] == White && hasCycle(colors, result, adj, graph))
                return true;
        }
        result.push_back(v);
        colors[v] = Black;
        return false;
    }
};
