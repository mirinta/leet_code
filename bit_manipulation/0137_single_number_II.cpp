#include <vector>

/**
 * Given an integer array nums where every element appears three times except for one, which appears
 * exactly once. Find the single element and return it.
 *
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! Each element in nums appears exactly three times except for one element which appears once.
 */

class Solution {
public:
    int singleNumber(std::vector<int>& nums)
    {
        // nums[i] in range [INT_MIN, INT_MAX]
        //           -2: [1110]
        //           -2: [1110]
        //           -2: [1110]
        //            3: [0011]
        // sum each bit: [3341]
        //     modulo 3: [0011]
        constexpr int kIntBits = CHAR_BIT * sizeof(int);
        long result = 0;
        for (int i = 0; i < kIntBits; ++i) {
            int count = 0;
            for (const auto& val : nums) {
                count += (val >> i) & 1;
            }
            result += (count % 3) << i; // equivalent to (count % 3) * std::pow(2, i)
        }
        return result;
    }
};