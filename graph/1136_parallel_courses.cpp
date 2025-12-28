#include <queue>
#include <vector>

/**
 * You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are
 * also given an array relations where relations[i] = [prevCourse_i, nextCourse_i], representing a
 * prerequisite relationship between course prevCourse_i and course nextCourse_i: course
 * prevCourse_i has to be taken before course nextCourse_i.
 *
 * In one semester, you can take any number of courses as long as you have taken all the
 * prerequisites in the previous semester for the courses you are taking.
 *
 * Return the minimum number of semesters needed to take all courses. If there is no way to take all
 * the courses, return -1.
 *
 * ! 1 <= n <= 5000
 * ! 1 <= relations.length <= 5000
 * ! relations[i].length == 2
 * ! 1 <= prevCourse_i, nextCourse_i <= n
 * ! prevCourse_i != nextCourse_i
 * ! All the pairs [prevCourse_i, nextCourse_i] are unique.
 */

class Solution {
public:
    int minimumSemesters(int n, std::vector<std::vector<int>>& relations)
    {
        // topological sorting, kahn's algorithm
        std::vector<std::vector<int>> graph(n);
        std::vector<int> indegrees(n, 0);
        for (const auto& relation : relations) {
            graph[relation[0] - 1].push_back(relation[1] - 1);
            indegrees[relation[1] - 1]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.emplace(i);
            }
        }
        int courses = 0;
        int result = 0;
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                const auto v = queue.front();
                queue.pop();
                courses++;
                for (const auto& w : graph[v]) {
                    if (--indegrees[w] == 0) {
                        queue.emplace(w);
                    }
                }
            }
            result++;
        }
        return courses == n ? result : -1;
    }
};