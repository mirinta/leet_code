#include <vector>

/**
 * You are given an integer array nums consisting of n elements, and an integer k.
 *
 * Find a contiguous subarray whose length is equal to k that has the maximum average value and
 * return this value. Any answer with a calculation error less than 10^-5 will be accepted.
 *
 * ! n == nums.length
 * ! 1 <= k <= n <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    double findMaxAverage(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int sum = 0;
        int max = INT_MIN;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            if (right - left + 1 > k) {
                sum -= nums[left];
                left++;
            }
            if (right - left + 1 == k) {
                max = std::max(max, sum);
            }
        }
        return static_cast<double>(max) / k;
    }
};