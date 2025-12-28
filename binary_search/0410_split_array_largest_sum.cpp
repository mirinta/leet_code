#include <vector>

/**
 * Given an integer array "nums" and an integer "k", split "nums" into "k" non-empty sub-arrays such
 * that the largest sum of any sub-array is minimized.
 *
 * Return the minimized largest sum of the split.
 *
 * A sub-array is contiguous part of the array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 10^6
 * ! 1 <= k <= min(50, nums.length)
 */

class Solution {
public:
    int splitArray(std::vector<int>& nums, int k)
    {
        // the max element is in one of the subarrays
        // so the min sum = max element,
        // and the max sum = sum of nums
        int lo = 0; // because 0 <= nums[i] <= 10^6
        int hi = 0;
        for (const auto& val : nums) {
            hi += val;
            lo = std::max(lo, val);
        }
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (canSplit(mid, k, nums)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool canSplit(int maxGroupSum, int maxGroups, const std::vector<int>& nums)
    {
        // | X X X | X X X | X X X |
        //   group1  group2  group3
        int groups = 1;
        int sum = 0;
        for (const auto& val : nums) {
            sum += val;
            if (sum > maxGroupSum) {
                sum = val;
                groups += 1;
            }
        }
        return groups <= maxGroups;
    }
};
