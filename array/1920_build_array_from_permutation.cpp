#include <vector>

/**
 * Given a zero-based permutation nums (0-indexed), build an array ans of the same length where
 * ans[i] = nums[nums[i]] for each 0 <= i < nums.length and return it.
 *
 * A zero-based permutation nums is an array of distinct integers from 0 to nums.length - 1
 * (inclusive).
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] < nums.length
 * ! The elements in nums are distinct.
 */

class Solution
{
public:
    std::vector<int> buildArray(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = nums[nums[i]];
        }
        return result;
    }
};
