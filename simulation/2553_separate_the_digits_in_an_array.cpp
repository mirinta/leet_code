#include <vector>

/**
 * Given an array of positive integers nums, return an array answer that consists of the digits of each integer in nums
 * after separating them in the same order they appear in nums.
 *
 * To separate the digits of an integer is to get all the digits it has in the same order.
 *
 * For example, for the integer 10921, the separation of its digits is [1,0,9,2,1].
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    std::vector<int> separateDigits(std::vector<int>& nums)
    {
        std::vector<int> result;
        auto helper = [&](int val) -> std::vector<int> {
            if (val == 0)
                return {0};

            std::vector<int> digits;
            while (val > 0) {
                digits.push_back(val % 10);
                val /= 10;
            }
            std::reverse(digits.begin(), digits.end());
            return digits;
        };
        for (const auto& val : nums) {
            const auto digits = helper(val);
            result.insert(result.end(), digits.begin(), digits.end());
        }
        return result;
    }
};
