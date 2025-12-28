#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums, which contains distinct elements and an integer k.
 *
 * A subset is called a k-Free subset if it contains no two elements with an absolute difference
 * equal to k. Notice that the empty set is a k-Free subset.
 *
 * Return the number of k-Free subsets of nums.
 *
 * A subset of an array is a selection of elements (possibly none) of the array.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 1000
 * ! 1 <= k <= 1000
 */

class Solution {
public:
    long long countTheNumOfKFreeSubsets(std::vector<int>& nums, int k)
    {
        // similar to LC.2597 (nums contains duplicate integers)
        // in this problem, nums contains only distinct integers
        std::unordered_map<int, std::vector<int>> map;
        for (const auto& val : nums) {
            map[val % k].push_back(val);
        }
        long long result = 1;
        for (auto& [key, group] : map) {
            std::sort(group.begin(), group.end());
            const int n = group.size();
            std::vector<long long> dp(n + 1, 0);
            dp[0] = 1;
            dp[1] = 2;
            for (int i = 2; i <= n; ++i) {
                const int curr = group[i - 1];
                const int prev = group[i - 2];
                if (curr - prev == k) {
                    dp[i] = dp[i - 1] + dp[i - 2];
                } else {
                    dp[i] = 2 * dp[i - 1];
                }
            }
            result *= dp[n];
        }
        return result;
    }
};