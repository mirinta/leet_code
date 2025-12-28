#include <algorithm>
#include <numeric>
#include <vector>

/**
 * Given an integer array nums and an integer k, return true if it is possible to divide this array
 * into k non-empty subsets whose sums are all equal.
 *
 * ! 1 <= k <= nums.length <= 16
 * ! 1 <= nums[i] <= 10^4
 * ! The frequency of each element is in the range [1, 4].
 */

class Solution {
public:
    bool canPartitionKSubsets(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    bool approach2(std::vector<int>& nums, int k)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0)
            return false;

        const int n = nums.size();
        const int target = total / k;
        std::vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int subset = 0; subset < dp.size(); ++subset) {
            if (dp[subset] == -1)
                continue;

            for (int i = 0; i < n; ++i) {
                if (!((subset >> i) & 1) && dp[subset] + nums[i] <= target) {
                    dp[subset | (1 << i)] = (dp[subset] + nums[i]) % target;
                }
            }
        }
        return dp.back() == 0;
    }

    bool approach1(std::vector<int>& nums, int k)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0)
            return false;

        const int target = total / k;
        std::vector<int> subset(k, 0);
        std::sort(nums.begin(), nums.end(), std::greater<>());
        return backtrack(subset, 0, k, target, nums);
    }

    bool backtrack(std::vector<int>& subset, int i, int k, int target, const std::vector<int>& nums)
    {
        if (i == nums.size())
            return true;

        if (nums[i] > target)
            return false;

        // check if it is possible to put nums[i] in subset[j]
        for (int j = 0; j < k; ++j) {
            // adding nums[i] to subset[j-1] is already checked
            // if subset[j] = subset[j-1], we don't need to check it again
            if (j > 0 && subset[j] == subset[j - 1])
                continue;

            if (subset[j] == target || subset[j] + nums[i] > target)
                continue;

            subset[j] += nums[i];
            if (backtrack(subset, i + 1, k, target, nums))
                return true;

            subset[j] -= nums[i];
        }
        return false;
    }
};
