#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
 *
 * You can do the following operation any number of times:
 *
 * - Increase or decrease any element of the array nums by 1.
 *
 * The cost of doing one operation on the ith element is cost[i].
 *
 * Return the minimum total cost such that all the elements of the array nums become equal.
 *
 * ! n == nums.length == cost.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums[i], cost[i] <= 10^6
 * ! Test cases are generated in a way that the output doesn't exceed 2^53-1
 */

class Solution {
public:
    long long minCost(std::vector<int>& nums, std::vector<int>& cost)
    {
        return approach2(nums, cost);
    }

private:
    long long approach2(std::vector<int>& nums, std::vector<int>& cost)
    {
        const int n = nums.size();
        std::vector<std::pair<long long, long long>> info(n);
        for (int i = 0; i < n; ++i) {
            info[i] = {nums[i], cost[i]};
        }
        std::sort(info.begin(), info.end());
        // find p such that sum(|nums[i] - p| * cost[i]) is minimized
        // consider cost[i] as the number of nums[i], i.e, we expand the original array
        // then p is the median of the new array
        const long long totalCost = std::accumulate(cost.begin(), cost.end(), 0LL);
        int mid = -1;
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += info[i].second;
            if (sum >= totalCost * 1.0 / 2) {
                mid = i;
                break;
            }
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::abs(info[i].first - info[mid].first) * info[i].second;
        }
        return result;
    }

    long long approach1(std::vector<int>& nums, std::vector<int>& cost)
    {
        const int n = nums.size();
        std::vector<std::pair<long long, long long>> info(n);
        for (int i = 0; i < n; ++i) {
            info[i] = {nums[i], cost[i]};
        }
        std::sort(info.begin(), info.end());
        // prefixCost[i] = cost of changing nums[0:i-1] to nums[i]
        std::vector<long long> prefixCost(n, 0);
        for (long long i = 1, accumulateCost = info[0].second; i < n; ++i) {
            prefixCost[i] = prefixCost[i - 1] + (info[i].first - info[i - 1].first) * accumulateCost;
            accumulateCost += info[i].second;
        }
        // suffixCost[i] = cost of changing nums[i+1:n-1] to nums[i]
        std::vector<long long> suffixCost(n, 0);
        for (long long i = n - 2, accumulateCost = info[n - 1].second; i >= 0; --i) {
            suffixCost[i] = suffixCost[i + 1] + (info[i + 1].first - info[i].first) * accumulateCost;
            accumulateCost += info[i].second;
        }
        long long result = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            result = std::min(result, prefixCost[i] + suffixCost[i]);
        }
        return result;
    }
};