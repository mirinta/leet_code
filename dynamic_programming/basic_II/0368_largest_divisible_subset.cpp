#include <algorithm>
#include <vector>

/**
 * Given a set of distinct positive integers "nums", return the largest subset answer such that
 * every pair (answer[i], answer[j]) of elements in this subset satisfies:
 *
 * - answer[i] % answer[j] == 0, or
 *
 * - answer[i] % answer[i] == 0
 *
 * If there are multiple solutions, return any of them.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 2 * 10^9
 * ! All the integers in nums are unique.
 */

class Solution {
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    std::vector<int> approach2(std::vector<int>& nums)
    {
        // dp[i] = max length of valid subset of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<int> dp(n, 1);
        std::sort(nums.begin(), nums.end());
        int maxLength = 0;
        int maxIndex = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] == 0) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            if (dp[i] > maxLength) {
                maxLength = dp[i];
                maxIndex = i;
            }
        }
        std::vector<int> result;
        result.reserve(dp[maxIndex]);
        for (int i = maxIndex; i >= 0; --i) {
            if (result.empty() || (result.size() + dp[i] == maxLength && result.back() % nums[i] == 0)) {
                result.push_back(nums[i]);
            }
        }
        return result;
    }

    std::vector<int> approach1(std::vector<int>& nums)
    {
        // dp[i] = largest valid subset of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n);
        std::sort(nums.begin(), nums.end());
        int maxLength = 0;
        int maxIndex = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] == 0 && dp[j].size() > dp[i].size()) {
                    dp[i] = dp[j];
                }
            }
            dp[i].push_back(nums[i]);
            if (dp[i].size() > maxLength) {
                maxLength = dp[i].size();
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }
};