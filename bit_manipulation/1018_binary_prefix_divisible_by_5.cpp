#include <vector>

/**
 * You are given a binary array nums (0-indexed).
 *
 * We define xi as the number whose binary representation is the subarray nums[0..i] (from
 * most-significant-bit to least-significant-bit).
 *
 * For example, if nums = [1,0,1], then x0 = 1, x1 = 2, and x2 = 5.
 *
 * Return an array of booleans answer where answer[i] is true if xi is divisible by 5.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution
{
public:
    std::vector<bool> prefixesDivBy5(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<bool> result(n);
        for (int i = 0, r = 0; i < n; ++i) {
            r = (2 * r % 5 + nums[i]) % 5;
            result[i] = r % 5 == 0;
        }
        return result;
    }
};
