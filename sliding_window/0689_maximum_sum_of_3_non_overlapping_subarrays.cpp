#include <vector>

/**
 * Given an integer array nums and an integer k, find three non-overlapping subarrays of length k
 * with maximum sum and return them.
 *
 * Return the result as a list of indices representing the starting position of each interval
 * (0-indexed). If there are multiple answers, return the lexicographically smallest one.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= nums[i] < 2^16
 * ! 1 <= k <= floor(nums.length / 3)
 */

class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        auto query = [&](int left, int right) { return presum[right + 1] - presum[left]; };
        // left[i] = the smallest j such that nums[j:j+k-1] has the largest sum among all subarrays
        // of nums with length k
        std::vector<int> left(n);
        for (int i = k - 1, maxSum = 0; i < n; ++i) {
            // check window [i-k+1:i]
            const int sum = query(i - k + 1, i);
            if (sum > maxSum) {
                maxSum = sum;
                left[i] = i - k + 1;
            } else {
                left[i] = left[i - 1];
            }
        }
        // right[i] = the smallest j such that nums[j:j+k-1] has the largest sum among all subarray
        // of nums with length k
        std::vector<int> right(n);
        for (int i = n - k, maxSum = 0; i >= 0; --i) {
            // check window [i:i+k-1]
            const int sum = query(i, i + k - 1);
            if (sum >= maxSum) {
                maxSum = sum;
                right[i] = i;
            } else {
                right[i] = right[i + 1];
            }
        }
        std::vector<int> result;
        for (int i = k, maxSum = 0; i + 2 * k - 1 < n; ++i) {
            // check window [j1:j1+k-1], [i:i+k-1], [j2,j2+k-1]
            const int j1 = left[i - 1];
            const int j2 = right[i + k];
            const int sum = query(j1, j1 + k - 1) + query(i, i + k - 1) + query(j2, j2 + k - 1);
            if (sum > maxSum) {
                maxSum = sum;
                result = {j1, i, j2};
            }
        }
        return result;
    }
};