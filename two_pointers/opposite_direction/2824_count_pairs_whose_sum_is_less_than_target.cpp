#include <algorithm>
#include <vector>

/**
 * Given a 0-indexed integer array nums of length n and an integer target, return the number of
 * pairs (i, j) where 0 <= i < j < n and nums[i] + nums[j] < target.
 *
 * ! 1 <= nums.length == n <= 50
 * ! -50 <= nums[i], target <= 50
 */

class Solution {
public:
    int countPairs(std::vector<int>& nums, int target)
    {
        if (nums.size() < 2)
            return 0;

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int left = 0;
        int right = n - 1;
        while (left < right) {
            if (nums[left] + nums[right] < target) {
                result += right - left; // (left,right),...,(left,left+1) are valid pairs
                left++;
            } else {
                right--;
            }
        }
        return result;
    }
};