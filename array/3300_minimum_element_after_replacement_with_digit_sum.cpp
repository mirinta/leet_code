#include <vector>

/**
 * You are given an integer array nums.
 *
 * You replace each element in nums with the sum of its digits.
 *
 * Return the minimum element in nums after all replacements.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int minElement(std::vector<int>& nums)
    {
        int result = INT_MAX;
        for (const auto& val : nums) {
            result = std::min(result, helper(val));
        }
        return result;
    }

private:
    int helper(int n)
    {
        int result = 0;
        while (n) {
            result += n % 10;
            n /= 10;
        }
        return result;
    }
};