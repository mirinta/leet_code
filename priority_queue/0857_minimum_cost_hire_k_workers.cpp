#include <algorithm>
#include <queue>
#include <vector>

/**
 * There are n workers. You are given two integer arrays quality and wage where quality[i] is the
 * quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
 *
 * We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay
 * them according to the following rules:
 *
 * - Every worker in the paid group must be paid at least their minimum wage expectation.
 *
 * - In the group, each worker's pay must be directly proportional to their quality. This means if a
 * worker’s quality is double that of another worker in the group, then they must be paid twice as
 * much as the other worker.
 *
 * Given the integer k, return the least amount of money needed to form a paid group satisfying the
 * above conditions. Answers within 10^-5 of the actual answer will be accepted.
 *
 * ! n == quality.length == wage.length
 * ! 1 <= k <= n <= 10^4
 * ! 1 <= quality[i], wage[i] <= 10^4
 */

class Solution {
public:
    double mincostToHireWorkers(std::vector<int>& quality, std::vector<int>& wage, int k)
    {
        // suppose we have a group {p1, p2, ..., pk}
        // then for each person pi:
        // total_cost * quality[pi] / total_quality >= wage[pi]
        // total_cost >= total_quality * wage[pi] / quality[pi]
        //
        // let ratio[pi] = wage[pi] / quality[pi],
        // then the minimum total_cost of the given group = total_quality * max(ratio[pi])
        const int n = quality.size();
        std::vector<std::pair<double, int>> ratio(n); // <ratio, person id>
        for (int i = 0; i < n; ++i) {
            ratio[i].first = wage[i] * 1.0 / quality[i];
            ratio[i].second = i;
        }
        std::sort(ratio.begin(), ratio.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        std::priority_queue<int, std::vector<int>, std::less<>> pq;
        int totalQuality = 0;
        for (int i = 0; i < k - 1; ++i) {
            totalQuality += quality[ratio[i].second];
            pq.push(quality[ratio[i].second]);
        }
        double result = DBL_MAX;
        for (int i = k - 1; i < n; ++i) {
            totalQuality += quality[ratio[i].second];
            const double totalCost = ratio[i].first * totalQuality;
            result = std::min(result, totalCost);
            pq.push(quality[ratio[i].second]);
            totalQuality -= pq.top();
            pq.pop();
        }
        return result;
    }
};