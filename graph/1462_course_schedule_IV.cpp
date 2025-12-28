#include <vector>

/**
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You
 * are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take
 * course ai first if you want to take course bi.
 *
 * For example, the pair [0, 1] indicates that you have to take course 0 before you can take
 * course 1. Prerequisites can also be indirect. If course a is a prerequisite of course b, and
 * course b is a prerequisite of course c, then course a is a prerequisite of course c.
 *
 * You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should
 * answer whether course uj is a prerequisite of course vj or not.
 *
 * Return a boolean array answer, where answer[j] is the answer to the jth query.
 *
 * ! 2 <= numCourses <= 100
 * ! 0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
 * ! prerequisites[i].length == 2
 * ! 0 <= ai, bi <= numCourses - 1
 * ! ai != bi
 * ! All the pairs [ai, bi] are unique.
 * ! The prerequisites graph has no cycles.
 * ! 1 <= queries.length <= 104
 * ! 0 <= ui, vi <= numCourses - 1
 * ! ui != vi
 */

class Solution {
public:
    std::vector<bool> checkIfPrerequisite(int numCourses,
                                          std::vector<std::vector<int>>& prerequisites,
                                          std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<bool>> reachable(numCourses, std::vector<bool>(numCourses, false));
        for (const auto& info : prerequisites) {
            reachable[info[0]][info[1]] = true;
        }
        for (int k = 0; k < numCourses; ++k) {
            reachable[k][k] = true;
            for (int i = 0; i < numCourses; ++i) {
                if (!reachable[i][k])
                    continue;

                for (int j = 0; j < numCourses; ++j) {
                    if (reachable[i][j] || !reachable[k][j])
                        continue;

                    reachable[i][j] = reachable[i][k] && reachable[k][j];
                }
            }
        }
        std::vector<bool> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            result.emplace_back(reachable[q[0]][q[1]]);
        }
        return result;
    }
};