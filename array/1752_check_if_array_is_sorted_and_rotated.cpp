#include <vector>

/**
 * Given an array nums, return true if the array was originally sorted in non-decreasing order, then
 * rotated some number of positions (including zero). Otherwise, return false.
 *
 * There may be duplicates in the original array.
 *
 * Note: An array A rotated by x positions results in an array B of the same length such that A[i]
 * == B[(i+x) % A.length], where % is the modulo operation.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    bool check(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    bool approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int count = 0;
        for (int i = 0; i < n; ++i) {
            count += nums[i] > nums[(i + 1) % n];
        }
        return count <= 1;
    }

    bool approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int i = 0;
        while (i + 1 < n && nums[i] <= nums[i + 1]) {
            i++;
        }
        if (i == n - 1)
            return true;

        if (nums[i + 1] > nums[0])
            return false;

        i += 1;
        while (i + 1 < n && nums[i] <= nums[i + 1]) {
            i++;
        }
        return i == n - 1 && nums[i] <= nums[0];
    }
};