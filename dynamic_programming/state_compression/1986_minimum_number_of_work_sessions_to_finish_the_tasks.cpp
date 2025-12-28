#include <vector>

/**
 * There are n tasks assigned to you. The task times are represented as an integer array tasks of
 * length n, where the ith task takes tasks[i] hours to finish. A work session is when you work for
 * at most sessionTime consecutive hours and then take a break.
 *
 * You should finish the given tasks in a way that satisfies the following conditions:
 *
 * - If you start a task in a work session, you must complete it in the same work session.
 *
 * - You can start a new task immediately after finishing the previous one.
 *
 * - You may complete the tasks in any order.
 *
 * Given tasks and sessionTime, return the minimum number of work sessions needed to finish all the
 * tasks following the conditions above.
 *
 * The tests are generated such that sessionTime is greater than or equal to the maximum element in
 * tasks[i].
 *
 * ! n == tasks.length
 * ! 1 <= n <= 14
 * ! 1 <= tasks[i] <= 10
 * ! max(tasks[i]) <= sessionTime <= 15
 */

class Solution {
public:
    int minSessions(std::vector<int>& tasks, int sessionTime)
    {
        return approach2(tasks, sessionTime);
    }

private:
    int approach2(const std::vector<int>& tasks, int sessionTime)
    {
        // dp[state] = min num of sessions to finish all tasks masked by state
        const int n = tasks.size();
        std::vector<int> dp(1 << n, INT_MAX / 2);
        for (int state = 0; state < dp.size(); ++state) {
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                if ((state >> i) & 1) {
                    sum += tasks[i];
                }
            }
            if (sum <= sessionTime) {
                dp[state] = 1;
            }
        }
        for (int state = 1; state < dp.size(); ++state) {
            for (int subset = state; subset > 0; subset = (subset - 1) & state) {
                dp[state] = std::min(dp[state], dp[subset] + dp[subset ^ state]);
            }
        }
        return dp.back();
    }

    int approach1(const std::vector<int>& tasks, int sessionTime)
    {
        const int n = tasks.size();
        std::vector<int> sessions;
        int result = n; // at most n sessions
        backtrack(result, sessions, 0, tasks, sessionTime);
        return result;
    }

    void backtrack(int& result, std::vector<int>& sessions, int i, const std::vector<int>& tasks, int sessionTime)
    {
        if (sessions.size() >= result)
            return;

        if (i == tasks.size()) {
            result = sessions.size();
            return;
        }
        for (int j = 0; j < sessions.size(); ++j) {
            if (sessions[j] + tasks[i] <= sessionTime) {
                sessions[j] += tasks[i];
                backtrack(result, sessions, i + 1, tasks, sessionTime);
                sessions[j] -= tasks[i];
            }
        }
        sessions.push_back(tasks[i]);
        backtrack(result, sessions, i + 1, tasks, sessionTime);
        sessions.pop_back();
    }
};