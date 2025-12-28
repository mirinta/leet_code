#include <map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * A subsequence of nums having length k and consisting of indices i0 < i1 < ... < ik-1 is balanced
 * if the following holds:
 *
 * - nums[ij] - nums[ij-1] >= ij - ij-1, for every j in the range [1, k - 1].
 *
 * A subsequence of nums having length 1 is considered balanced.
 *
 * Return an integer denoting the maximum possible sum of elements in a balanced subsequence of
 * nums.
 *
 * A subsequence of an array is a new non-empty array that is formed from the original array by
 * deleting some (possibly none) of the elements without disturbing the relative positions of the
 * remaining elements.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long maxBalancedSubsequenceSum(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // DP with ordered map, time O(NlogN), space O(N)
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // nums[i]-nums[j]>=i-j is equivalent to nums[i]-i>=nums[j]-j
        // let map[x]=dp[i], where x=nums[i]-i
        // x is sorted and we need to make map[x] sorted
        std::map<int, long long> map;
        for (int i = 0; i < n; ++i) {
            const int x = nums[i] - i;
            auto iter = map.upper_bound(x); // first element > nums[i]-i
            if (iter != map.begin()) {
                map[x] = std::max<long long>(nums[i], std::prev(iter)->second + nums[i]);
            } else {
                map[x] = nums[i];
            }
            while (iter != map.end() && iter->second <= map[x]) {
                map.erase(iter++);
            }
        }
        return map.empty() ? LLONG_MIN : map.rbegin()->second;
    }

    // #TLE# DP, time O(N^2), space O(N)
    long long approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = max sum of elements in a balanced subsequence ending at nums[i]
        // base case:
        // - dp[i] = nums[i], a subsequence having length 1 is considered as balanced
        std::vector<long long> dp(n);
        long long result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp[i] = nums[i];
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] - nums[j] >= i - j) {
                    dp[i] = std::max(dp[i], dp[j] + nums[i]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};
