#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return the length of the longest strictly increasing subsequence.
 *
 * ! Can you come up with an algorithm that runs in O(nlogn) time complexity?
 *
 * ! 1 <= nums.length <= 2500
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    int lengthOfLIS(const std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // Binary search, time O(NlogN), space O(N)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> v; // strictly increasing
        for (const auto& val : nums) {
            if (v.empty() || val > v.back()) {
                v.push_back(val);
                continue;
            }
            auto iter = std::lower_bound(v.begin(), v.end(), val);
            if (iter != v.end()) {
                *iter = val;
            }
        }
        return v.size();
    }

    // DP, time O(N), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        // dp[i] = length of LIS ending at nums[i]
        // X X X X X j X i
        // |<-dp[j]->|
        // |<---dp[i]--->|
        std::vector<int> dp(n, 1); // each character itself is a strictly increasing subsequence
        int result = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    dp[i] = std::max(dp[i], 1 + dp[j]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};
