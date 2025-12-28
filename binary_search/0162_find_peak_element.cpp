#include <vector>

/**
 * A peak element is an element that is strictly greater than its neighbors.
 *
 * Given a 0-indexed integer array nums, find a peak element, and return its index. If the array
 * contains multiple peaks, return the index to any of the peaks.
 *
 * You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to
 * be strictly greater than a neighbor that is outside the array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * ! 1 <= nums.length <= 1000
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! nums[i] != nums[i + 1] for all valid i.
 */

class Solution {
public:
    int findPeakElement(std::vector<int>& nums)
    {
        // nums[i] != nums[i + 1] for all valid i
        // thus, the problem definitely has a solution
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (nums[mid] > nums[mid - 1]) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

    int approach1(const std::vector<int>& nums)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid + 1] > nums[mid]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
};
