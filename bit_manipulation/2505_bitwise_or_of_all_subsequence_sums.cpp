#include <array>
#include <vector>

/**
 * Given an integer array nums, return the value of the bitwise OR of the sum of all possible
 * subsequences in the array.
 *
 * A subsequence is a sequence that can be derived from another sequence by removing zero or more
 * elements without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long subsequenceSumOr(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    long long approach2(const std::vector<int>& nums)
    {
        long long sum = 0;
        long long result = 0;
        for (const auto& val : nums) {
            sum += val;
            result |= val;
            result |= sum;
        }
        return result;
    }

    long long approach1(const std::vector<int>& nums)
    {
        std::array<int, 64> count{};
        for (const auto& val : nums) {
            for (int i = 0; i < 32; ++i) {
                count[i] += (val >> i) & 1;
            }
        }
        long long result = 0;
        for (int i = 0; i < 64; ++i) {
            if (count[i] > 0) {
                result |= 1LL << i;
            }
            if (i + 1 < 64) {
                count[i + 1] += count[i] / 2;
            }
        }
        return result;
    }
};