#include <vector>

/**
 * Given the array of integers nums, you will choose two different indices i and j of that array.
 * Return the maximum value of (nums[i]-1)*(nums[j]-1).
 *
 * ! 2 <= nums.length <= 500
 * ! 1 <= nums[i] <= 10^3
 */

class Solution {
public:
    int maxProduct(std::vector<int>& nums)
    {
        int max = INT_MIN;
        int secondMax = INT_MIN;
        for (const auto& val : nums) {
            if (val > max) {
                secondMax = max;
                max = val;
            } else if (val > secondMax) {
                secondMax = val;
            }
        }
        return (max - 1) * (secondMax - 1);
    }
};