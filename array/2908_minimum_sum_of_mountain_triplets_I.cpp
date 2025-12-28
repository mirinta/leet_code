#include <vector>

/**
 * You are given a 0-indexed array nums of integers.
 *
 * A triplet of indices (i, j, k) is a mountain if:
 *
 * - i < j < k
 *
 * - nums[i] < nums[j] and nums[k] < nums[j]
 *
 * Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return
 * -1.
 *
 * ! 3 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int minimumSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        if (n < 3)
            return -1;

        // ... i ... j ... k ...
        int result = INT_MAX;
        for (int j = 1; j < n - 1; ++j) {
            int minOfNumsI = INT_MAX;
            for (int i = j - 1; i >= 0; --i) {
                if (nums[i] < nums[j]) {
                    minOfNumsI = std::min(minOfNumsI, nums[i]);
                }
            }
            int minOfNumsK = INT_MAX;
            for (int k = j + 1; k < n; ++k) {
                if (nums[k] < nums[j]) {
                    minOfNumsK = std::min(minOfNumsK, nums[k]);
                }
            }
            if (minOfNumsI == INT_MAX || minOfNumsK == INT_MAX)
                continue;

            result = std::min(result, minOfNumsI + nums[j] + minOfNumsK);
        }
        return result == INT_MAX ? -1 : result;
    }
};