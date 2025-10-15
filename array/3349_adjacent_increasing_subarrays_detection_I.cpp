#include <vector>

/**
 * Given an array nums of n integers and an integer k, determine whether there exist two adjacent
 * subarrays of length k such that both subarrays are strictly increasing. Specifically, check if
 * there are two subarrays starting at indices a and b (a < b), where:
 *
 * - Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
 *
 * - The subarrays must be adjacent, meaning b = a + k.
 *
 * Return true if it is possible to find two such subarrays, and false otherwise.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 < 2 * k <= nums.length
 * ! -1000 <= nums[i] <= 1000
 */

class Solution
{
public:
    bool hasIncreasingSubarrays(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        for (int i = 0; i + 2 * k - 1 < n; ++i) {
            if (isValid(i, i + k - 1, nums) && isValid(i + k, i + 2 * k - 1, nums))
                return true;
        }
        return false;
    }

private:
    // check if nums[lo:hi] is strictly increasing
    bool isValid(int lo, int hi, const std::vector<int>& nums)
    {
        for (int i = lo + 1; i <= hi; ++i) {
            if (nums[i] <= nums[i - 1])
                return false;
        }
        return true;
    }
};
