#include <queue>
#include <vector>

/**
 * You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are
 * also given a 2D integer array relations where relations[j] = [prevCoursej, nextCoursej] denotes
 * that course prevCoursej has to be completed before course nextCoursej (prerequisite
 * relationship). Furthermore, you are given a 0-indexed integer array time where time[i] denotes
 * how many months it takes to complete the (i+1)th course.
 *
 * You must find the minimum number of months needed to complete all the courses following these
 * rules:
 *
 * - You may start taking a course at any time if the prerequisites are met.
 *
 * - Any number of courses can be taken at the same time.
 *
 * Return the minimum number of months needed to complete all the courses.
 *
 * Note: The test cases are generated such that it is possible to complete every course (i.e., the
 * graph is a directed acyclic graph).
 *
 * ! 1 <= n <= 5 * 10^4
 * ! 0 <= relations.length <= min(n * (n - 1) / 2, 5 * 10^4)
 * ! relations[j].length == 2
 * ! 1 <= prevCoursej, nextCoursej <= n
 * ! prevCoursej != nextCoursej
 * ! All the pairs [prevCoursej, nextCoursej] are unique.
 * ! time.length == n
 * ! 1 <= time[i] <= 10^4
 * ! The given graph is a directed acyclic graph.
 */

class Solution {
public:
    int minimumTime(int n, std::vector<std::vector<int>>& relations, std::vector<int>& time)
    {
        // The given graph is a directed acyclic graph.
        std::vector<std::vector<int>> graph(n);
        std::vector<int> indegrees(n, 0);
        for (const auto& relation : relations) {
            const auto& prev = relation[0] - 1; // to 0-indexed
            const auto& next = relation[1] - 1; // to 0-indexed
            graph[prev].push_back(next);
            indegrees[next]++;
        }
        std::vector<int> maxTime(n, 0); // maxTime[i] = max time to complete course i
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.push(i);
                maxTime[i] = time[i];
            }
        }
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            for (const auto& adj : graph[v]) {
                maxTime[adj] = std::max(maxTime[adj], maxTime[v] + time[adj]);
                if (--indegrees[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        return *std::max_element(maxTime.begin(), maxTime.end());
    }
};
