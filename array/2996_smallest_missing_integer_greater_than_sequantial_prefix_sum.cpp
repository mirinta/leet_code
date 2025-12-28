#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed array of integers nums.
 *
 * A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. In
 * particular, the prefix consisting only of nums[0] is sequential.
 *
 * Return the smallest integer x missing from nums such that x is greater than or equal to the sum
 * of the longest sequential prefix.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int missingInteger(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_set<int> set(nums.begin(), nums.end());
        int i = 1;
        int result = nums[0];
        while (i < n && nums[i] - nums[i - 1] == 1) {
            result += nums[i];
            i++;
        }
        while (set.count(result)) {
            result++;
        }
        return result;
    }
};