#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed array nums comprising of n non-negative integers.
 *
 * In one operation, you must:
 *
 * - Choose an integer i such that 1 <= i < n and nums[i] > 0.
 *
 * - Decrease nums[i] by 1.
 *
 * - Increase nums[i - 1] by 1.
 *
 * Return the minimum possible value of the maximum integer of nums after performing any number of
 * operations.
 *
 * ! n == nums.length
 * ! 2 <= n <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minimizeArrayValue(std::vector<int>& nums)
    {
        int lo = nums[0];
        int hi = *std::max_element(nums.begin(), nums.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int max, const std::vector<int>& nums)
    {
        long long diff = 0;
        for (const auto& val : nums) {
            diff += max - val;
            if (diff < 0)
                return false;
        }
        return true;
    }
};