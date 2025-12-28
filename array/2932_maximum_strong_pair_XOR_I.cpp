#include <vector>

/**
 * You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair
 * if it satisfies the condition:
 *
 * - |x - y| <= min(x, y)
 *
 * You need to select two integers from nums such that they form a strong pair and their bitwise XOR
 * is the maximum among all strong pairs in the array.
 *
 * Return the maximum XOR value out of all possible strong pairs in the array nums.
 *
 * Note that you can pick the same integer twice to form a pair.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int maximumStrongPairXor(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (std::abs(nums[i] - nums[j]) <= std::min(nums[i], nums[j])) {
                    result = std::max(result, nums[i] ^ nums[j]);
                }
            }
        }
        return result;
    }
};