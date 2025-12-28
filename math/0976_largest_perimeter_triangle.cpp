#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, return the largest perimeter of a triangle with a non-zero area,
 * formed from three of these lengths. If it is impossible to form any triangle of a non-zero area,
 * return 0.
 *
 * ! 3 <= nums.length <= 10^4
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    int largestPerimeter(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return 0;

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        for (int i = n - 1; i >= 2; --i) {
            if (nums[i - 2] + nums[i - 1] > nums[i])
                return nums[i - 2] + nums[i - 1] + nums[i];
        }
        return 0;
    }
};
