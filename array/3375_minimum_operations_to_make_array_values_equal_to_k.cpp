#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums and an integer k.
 *
 * An integer h is called valid if all values in the array that are strictly greater than h are
 * identical.
 *
 * For example, if nums = [10, 8, 10, 8], a valid integer is h = 9 because all nums[i] > 9 are equal
 * to 10, but 5 is not a valid integer.
 *
 * You are allowed to perform the following operation on nums:
 *
 * - Select an integer h that is valid for the current values in nums.
 *
 * - For each index i where nums[i] > h, set nums[i] to h.
 *
 * Return the minimum number of operations required to make every element in nums equal to k. If it
 * is impossible to make all elements equal to k, return -1.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 * ! 1 <= k <= 100
 */

class Solution
{
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        std::unordered_set<int> set;
        for (const auto& val : nums) {
            if (val < k)
                return -1;

            if (val > k) {
                set.insert(val);
            }
        }
        return set.size();
    }
};
