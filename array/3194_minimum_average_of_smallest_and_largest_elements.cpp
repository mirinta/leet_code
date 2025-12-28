#include <algorithm>
#include <vector>

/**
 * You have an array of floating point numbers averages which is initially empty. You are given an
 * array nums of n integers where n is even.
 *
 * You repeat the following procedure n / 2 times:
 *
 * - Remove the smallest element, minElement, and the largest element maxElement, from nums.
 *
 * - Add (minElement + maxElement) / 2 to averages.
 *
 * Return the minimum element in averages.
 *
 * ! 2 <= n == nums.length <= 50
 * ! n is even.
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    double minimumAverage(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        double result = DBL_MAX;
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            result = std::min(result, (nums[i] + nums[j]) / 2.0);
        }
        return result;
    }
};