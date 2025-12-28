#include <vector>

/**
 * You are given a 0-indexed integer array nums of size n, and a 0-indexed integer array pattern of
 * size m consisting of integers -1, 0, and 1.
 *
 * A subarray nums[i..j] of size m + 1 is said to match the pattern if the following conditions hold
 * for each element pattern[k]:
 *
 * - nums[i + k + 1] > nums[i + k] if pattern[k] == 1.
 *
 * - nums[i + k + 1] == nums[i + k] if pattern[k] == 0.
 *
 * - nums[i + k + 1] < nums[i + k] if pattern[k] == -1.
 *
 * Return the count of subarrays in nums that match the pattern.
 *
 * ! 2 <= n == nums.length <= 100
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= m == pattern.length < n
 * ! -1 <= pattern[i] <= 1
 */

class Solution {
public:
    int countMatchingSubarrays(std::vector<int>& nums, std::vector<int>& pattern)
    {
        const int n = nums.size();
        const int m = pattern.size();
        int result = 0;
        for (int i = 0; i + m < n; ++i) {
            bool isValid = true;
            for (int k = 0; k < m; ++k) {
                const bool case1 = pattern[k] == 1 && nums[i + k + 1] > nums[i + k];
                const bool case2 = pattern[k] == 0 && nums[i + k + 1] == nums[i + k];
                const bool case3 = pattern[k] == -1 && nums[i + k + 1] < nums[i + k];
                if (!case1 && !case2 && !case3) {
                    isValid = false;
                    break;
                }
            }
            result += isValid;
        }
        return result;
    }
};