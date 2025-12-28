#include <vector>

/**
 * The score of an array is defined as the product of its sum and its length.
 *
 * - For example, the score of [1, 2, 3, 4, 5] is (1 + 2 + 3 + 4 + 5) * 5 = 75.
 *
 * Given a positive integer array nums and an integer k, return the number of non-empty subarrays of
 * nums whose score is strictly less than k.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= 10^15
 */

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums, long long k)
    {
        const int n = nums.size();
        long long sum = 0;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum * (right - left + 1) >= k) {
                sum -= nums[left];
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};