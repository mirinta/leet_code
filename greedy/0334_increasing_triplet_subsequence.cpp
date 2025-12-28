#include <vector>

/**
 * Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that
 * i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.
 *
 * ! 1 <= nums.length <= 5 * 10^5
 * ! -2^31 <= nums[i] <= 2^31 - 1
 */

class Solution {
public:
    bool increasingTriplet(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return false;

        int i = INT_MAX;
        int j = INT_MAX;
        for (const auto& val : nums) {
            if (val <= i) {
                i = val;
            } else if (val <= j) {
                j = val;
            } else {
                return true;
            }
        }
        return false;
    }
};