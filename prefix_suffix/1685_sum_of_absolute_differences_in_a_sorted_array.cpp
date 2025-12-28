#include <numeric>
#include <vector>

/**
 * You are given an integer array nums sorted in non-decreasing order.
 *
 * Build and return an integer array result with the same length as nums such that result[i] is
 * equal to the summation of absolute differences between nums[i] and all the other elements in the
 * array.
 *
 * In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j !=
 * i (0-indexed).
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= nums[i + 1] <= 10^4
 */

class Solution {
public:
    std::vector<int> getSumAbsoluteDifferences(std::vector<int>& nums)
    {
        // result[i] = (i+1)*nums[i]-sum(nums[0:i])+sum(nums[i+1:n-1])-(n-i-1)*nums[i]
        // - total_sum = sum(nums[0:i])+sum(nums[i+1:n-1])
        // - result[i] = nums[i]*(2i+2-n)-total_sum-2*sum(nums[0:i])
        const int n = nums.size();
        const int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
        int prefixSum = 0;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            prefixSum += nums[i];
            result[i] = nums[i] * (2 * i - n + 2) + totalSum - 2 * prefixSum;
        }
        return result;
    }
};