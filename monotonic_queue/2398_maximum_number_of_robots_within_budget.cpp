#include <queue>
#include <set>
#include <vector>

/**
 * You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both
 * of length n. The ith robot costs chargeTimes[i] units to charge and costs runningCosts[i] units
 * to run. You are also given an integer budget.
 *
 * The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts),
 * where max(chargeTimes) is the largest charge cost among the k robots and sum(runningCosts) is the
 * sum of running costs among the k robots.
 *
 * Return the maximum number of consecutive robots you can run such that the total cost does not
 * exceed budget.
 *
 * ! chargeTimes.length == runningCosts.length == n
 * ! 1 <= n <= 5 * 10^4
 * ! 1 <= chargeTimes[i], runningCosts[i] <= 10^5
 * ! 1 <= budget <= 10^15
 */

class Solution {
public:
    int maximumRobots(std::vector<int>& chargeTimes, std::vector<int>& runningCosts, long long budget)
    {
        return approach2(chargeTimes, runningCosts, budget);
    }

private:
    // sliding window + monotonic queue, time O(N), space O(N)
    int approach2(const std::vector<int>& chargeTimes, const std::vector<int>& runningCosts, long long budget)
    {
        const int n = chargeTimes.size();
        std::vector<long long> prefixSum(n + 1, 0); // prefixSum[i] = sum of runningCosts[0:i-1]
        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + runningCosts[i - 1];
        }
        std::deque<long long> maxDeque; // front is the max element
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (!maxDeque.empty() && chargeTimes[right] > maxDeque.back()) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(chargeTimes[right]);
            while (left <= right &&
                   (maxDeque.front() + (right - left + 1) * (prefixSum[right + 1] - prefixSum[left]) > budget)) {
                if (maxDeque.front() == chargeTimes[left]) {
                    maxDeque.pop_front();
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // sliding window + multiset, time O(NlogN), space O(N)
    int approach1(const std::vector<int>& chargeTimes, const std::vector<int>& runningCosts, long long budget)
    {
        const int n = chargeTimes.size();
        std::vector<long long> prefixSum(n + 1, 0); // prefixSum[i] = sum of runningCosts[0:i-1]
        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + runningCosts[i - 1];
        }
        std::multiset<long long> set;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            set.insert(chargeTimes[right]);
            while (left <= right &&
                   (*set.rbegin() + (right - left + 1) * (prefixSum[right + 1] - prefixSum[left])) > budget) {
                set.erase(set.find(chargeTimes[left]));
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
