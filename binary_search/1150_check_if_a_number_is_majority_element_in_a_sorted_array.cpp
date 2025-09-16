#include <vector>

/**
 * Given an integer array "nums" sorted in non-decreasing order and an integer "target", return true
 * if target is a majority element, or false otherwise.
 *
 * A majority element in an array is an element that appears more than nums.length / 2 times in the
 * array.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i], target <= 10^9
 * ! nums is sorted in non-decreasing order.
 */

class Solution
{
public:
    bool isMajorityElement(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        const int firstIdx = findFirst(target, nums);
        if (firstIdx < 0)
            return false;

        return firstIdx + n / 2 < n && nums[firstIdx + n / 2] == target;
    }

private:
    int findFirst(int target, const std::vector<int>& nums)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo < nums.size() && nums[lo] == target ? lo : -1;
    }
};