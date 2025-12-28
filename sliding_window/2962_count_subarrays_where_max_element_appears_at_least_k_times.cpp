#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and a positive integer k.
 *
 * Return the number of subarrays where the maximum element of nums appears at least k times in that
 * subarray.
 *
 * A subarray is a contiguous sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const int max = *std::max_element(nums.begin(), nums.end());
        int count = 0;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            count += nums[right] == max;
            while (count >= k) {
                count -= nums[left] == max;
                left++;
            }
            result += left;
        }
        return result;
    }
};