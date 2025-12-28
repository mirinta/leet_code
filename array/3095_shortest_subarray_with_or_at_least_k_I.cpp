#include <vector>

/**
 * You are given an array nums of non-negative integers and an integer k.
 *
 * An array is called special if the bitwise OR of all of its elements is at least k.
 *
 * Return the length of the shortest special non-empty subarray of nums, or return -1 if no special
 * subarray exists.
 *
 * ! 1 <= nums.length <= 50
 * ! 0 <= nums[i] <= 50
 * ! 0 <= k < 64
 */

class Solution {
public:
    int minimumSubarrayLength(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i, score = 0; j < n; ++j) {
                score |= nums[j];
                if (score >= k) {
                    result = std::min(result, j - i + 1);
                }
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};