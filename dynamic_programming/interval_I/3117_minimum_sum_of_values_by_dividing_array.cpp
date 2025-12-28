#include <unordered_map>
#include <vector>

/**
 * You are given two arrays nums and andValues of length n and m respectively.
 *
 * The value of an array is equal to the last element of that array.
 *
 * You have to divide nums into m disjoint contiguous subarrays such that for the ith subarray [li,
 * ri], the bitwise AND of the subarray elements is equal to andValues[i], in other words, nums[li]
 * & nums[li + 1] & ... & nums[ri] == andValues[i] for all 1 <= i <= m, where & represents the
 * bitwise AND operator.
 *
 * Return the minimum possible sum of the values of the m subarrays nums is divided into. If it is
 * not possible to divide nums into m subarrays satisfying these conditions, return -1.
 *
 * ! 1 <= n == nums.length <= 10^4
 * ! 1 <= m == andValues.length <= min(n, 10)
 * ! 1 <= nums[i] < 10^5
 * ! 0 <= andValues[j] < 10^5
 */

class Solution {
public:
    int minimumValueSum(std::vector<int>& nums, std::vector<int>& andValues)
    {
        const int n = nums.size();
        const int m = andValues.size();
        std::vector<std::vector<std::unordered_map<int, int>>> memo(n + 1,
                                                                    std::vector<std::unordered_map<int, int>>(m + 1));
        const int result = dp(memo, 0, 0, -1, nums, andValues);
        return result == kMax ? -1 : result;
    }

private:
    static constexpr int kMax = INT_MAX / 2;

    int dp(std::vector<std::vector<std::unordered_map<int, int>>>& memo,
           int i,
           int j,
           int AND,
           const std::vector<int>& nums,
           const std::vector<int>& andValues)
    {
        if (i == nums.size())
            return j == andValues.size() ? 0 : kMax;

        if (j == andValues.size())
            return kMax;

        if (memo[i][j].count(AND))
            return memo[i][j][AND];

        int result = kMax;
        result = std::min(result, dp(memo, i + 1, j, AND & nums[i], nums, andValues));
        if ((AND & nums[i]) == andValues[j]) {
            result = std::min(result, dp(memo, i + 1, j + 1, -1, nums, andValues) + nums[i]);
        }
        return memo[i][j][AND] = result;
    }
};