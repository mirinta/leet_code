#include <queue>
#include <vector>

/**
 * A company is organizing a meeting and has a list of n employees, waiting to be invited. They have
 * arranged for a large circular table, capable of seating any number of employees.
 *
 * The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will
 * attend the meeting only if they can sit next to their favorite person at the table. The favorite
 * person of an employee is not themself.
 *
 * Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the
 * ith employee, return the maximum number of employees that can be invited to the meeting.
 *
 * ! n == favorite.length
 * ! 2 <= n <= 10^5
 * ! 0 <= favorite[i] <= n - 1
 * ! favorite[i] != i
 */

class Solution {
public:
    int maximumInvitations(std::vector<int>& favorite)
    {
        const int n = favorite.size();
        std::vector<int> indegrees(n);
        for (int i = 0; i < n; ++i) {
            indegrees[favorite[i]]++;
        }
        std::queue<int> queue;
        for (int i = 0; i < n; ++i) {
            if (indegrees[i] == 0) {
                queue.emplace(i);
            }
        }
        std::vector<bool> visited(n, false);
        std::vector<int> depth(n, 1);
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            visited[v] = true;
            if (--indegrees[favorite[v]] == 0) {
                queue.emplace(favorite[v]);
            }
            depth[favorite[v]] = depth[v] + 1;
        }
        int case1 = 0; // max length of cycles with at least 3 nodes
        int case2 = 0; // total length of cycles with exactly 2 nodes + length of 2 single links
        for (int i = 0; i < n; ++i) {
            if (visited[i])
                continue;

            int node = i;
            int count = 0; // num of nodes in this cycle
            while (!visited[node]) {
                count++;
                visited[node] = true;
                node = favorite[node];
            }
            if (count >= 3) {
                case1 = std::max(case1, count);
            } else if (count == 2) {
                case2 += depth[i] + depth[favorite[i]];
            }
        }
        return std::max(case1, case2);
    }
};