#include <vector>

/**
 * 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
 *
 * 如果有多对数字的和等于s，则输出任意一对即可。
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        if (nums.size() < 2)
            return {};

        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            const int sum = nums[lo] + nums[hi];
            if (sum > target) {
                hi--;
            } else if (sum < target) {
                lo++;
            } else {
                return {nums[lo], nums[hi]};
            }
        }
        return {};
    }
};