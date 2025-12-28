#include <array>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * We call a subarray of nums nice if the bitwise AND of every pair of elements that are in
 * different positions in the subarray is equal to 0.
 *
 * Return the length of the longest nice subarray.
 *
 * A subarray is a contiguous part of an array.
 *
 * Note that subarrays of length 1 are always considered nice.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int longestNiceSubarray(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int left = 0, right = 0, OR = 0; right < n; ++right) {
            while (OR & nums[right]) {
                OR ^= nums[left++];
            }
            result = std::max(result, right - left + 1);
            OR |= nums[right];
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        std::array<int, 32> count{};
        auto isValid = [&count]() {
            for (const auto& freq : count) {
                if (freq > 1)
                    return false;
            }
            return true;
        };
        auto update = [&count](int val, int delta) {
            for (int i = 0; i < 32; ++i) {
                if ((val >> i) & 1) {
                    count[i] += delta;
                }
            }
        };
        const int n = nums.size();
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            update(nums[right], 1);
            while (!isValid()) {
                update(nums[left++], -1);
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
