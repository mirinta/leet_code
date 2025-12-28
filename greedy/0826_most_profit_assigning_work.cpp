#include <algorithm>
#include <vector>

/**
 * You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:
 *
 * - difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
 *
 * - worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with
 * difficulty at most worker[j]).
 *
 * Every worker can be assigned at most one job, but one job can be completed multiple times.
 *
 * - For example, if three workers attempt the same job that pays $1, then the total profit will be
 * $3. If a worker cannot complete any job, their profit is $0.
 *
 * Return the maximum profit we can achieve after assigning the workers to the jobs.
 *
 * ! n == difficulty.length
 * ! n == profit.length
 * ! m == worker.length
 * ! 1 <= n, m <= 10^4
 * ! 1 <= difficulty[i], profit[i], worker[i] <= 10^5
 */

class Solution {
public:
    int maxProfitAssignment(std::vector<int>& difficulty, std::vector<int>& profit, std::vector<int>& worker)
    {
        const int n = difficulty.size();
        std::vector<std::pair<int, int>> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i].first = difficulty[i];
            jobs[i].second = profit[i];
        }
        std::sort(jobs.begin(), jobs.end(), [](const auto& j1, const auto& j2) { return j1.first < j2.first; });
        for (int i = 1; i < n; ++i) {
            jobs[i].second = std::max(jobs[i - 1].second, jobs[i].second);
        }
        int result = 0;
        for (const auto& val : worker) {
            auto iter =
                std::upper_bound(jobs.begin(), jobs.end(), val, [](int val, const auto& p) { return p.first > val; });
            if (iter != jobs.begin()) {
                result += std::prev(iter)->second;
            }
        }
        return result;
    }
};