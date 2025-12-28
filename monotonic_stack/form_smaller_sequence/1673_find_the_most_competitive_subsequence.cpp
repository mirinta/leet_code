#include <vector>

/**
 * Given an integer array nums and a positive integer k, return the most competitive subsequence of
 * nums of size k.
 *
 * An array's subsequence is a resulting sequence obtained by erasing some (possibly zero) elements
 * from the array.
 *
 * We define that a subsequence a is more competitive than a subsequence b (of the same length) if
 * in the first position where a and b differ, subsequence a has a number less than the
 * corresponding number in b. For example, [1,3,4] is more competitive than [1,3,5] because the
 * first position they differ is at the final number, and 4 is less than 5.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    std::vector<int> mostCompetitive(std::vector<int>& nums, int k)
    {
        // similar to LC.402
        int remove = nums.size() - k;
        std::vector<int> result;
        for (const auto& val : nums) {
            while (remove > 0 && !result.empty() && val < result.back()) {
                result.pop_back();
                remove--;
            }
            result.push_back(val);
        }
        while (remove > 0) {
            result.pop_back();
            remove--;
        }
        return result;
    }
};