#include <array>
#include <vector>

/**
 * You are given an array nums of non-negative integers and an integer k.
 *
 * An array is called special if the bitwise OR of all of its elements is at least k.
 *
 * Return the length of the shortest special non-empty subarray of nums, or return -1 if no special
 * subarray exists.
 *
 * ! 1 <= nums.length <= 2 * 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^9
 */

class Solution {
public:
    int minimumSubarrayLength(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::array<int, 32> count{};
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            update(count, nums[right], 1);
            while (left <= right && value(count) >= k) {
                result = std::min(result, right - left + 1);
                update(count, nums[left], -1);
                left++;
            }
        }
        return result == INT_MAX ? -1 : result;
    }

private:
    void update(std::array<int, 32>& count, int val, int delta)
    {
        for (int i = 0; i < 32; ++i) {
            if ((val >> i) & 1) {
                count[i] += delta;
            }
        }
    }

    int value(const std::array<int, 32>& count)
    {
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            if (count[i] > 0) {
                result |= 1 << i;
            }
        }
        return result;
    }
};