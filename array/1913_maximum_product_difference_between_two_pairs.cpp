#include <vector>

/**
 * The product difference between two pairs (a, b) and (c, d) is defined as (a * b) - (c * d).
 *
 * For example, the product difference between (5, 6) and (2, 7) is (5 * 6) - (2 * 7) = 16.
 * Given an integer array nums, choose four distinct indices w, x, y, and z such that the product
 * difference between pairs (nums[w], nums[x]) and (nums[y], nums[z]) is maximized.
 *
 * Return the maximum such product difference.
 *
 * ! 4 <= nums.length <= 10^4
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int maxProductDifference(std::vector<int>& nums)
    {
        // find the top 2 largest and the top 2 smallest
        int max = INT_MIN;
        int secondMax = INT_MIN;
        int min = INT_MAX;
        int secondMin = INT_MAX;
        for (const auto& val : nums) {
            if (val > max) {
                secondMax = max;
                max = val;
            } else if (val > secondMax) {
                secondMax = val;
            }
            if (val < min) {
                secondMin = min;
                min = val;
            } else if (val < secondMin) {
                secondMin = val;
            }
        }
        return max * secondMax - (min * secondMin);
    }
};