#include <vector>

/**
 * Given a circular array nums, find the maximum absolute difference between adjacent elements.
 *
 * Note: In a circular array, the first and last elements are adjacent.
 *
 * ! 2 <= nums.length <= 100
 * ! -100 <= nums[i] <= 100
 */

class Solution
{
public:
    int maxAdjacentDistance(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, std::abs(nums[i] - nums[(i + 1) % n]));
        }
        return result;
    }
};
