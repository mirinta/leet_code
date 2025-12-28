#include <vector>

/**
 * Given an unsorted integer array nums, return the smallest missing positive integer.
 *
 * You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -2^31 <= nums[i] <= 2^31 - 1
 */

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums)
    {
        const int n = nums.size();
        nums.insert(nums.begin(), 0);
        for (int i = 1; i <= n; ++i) {
            while (nums[i] > 0 && nums[i] != i && nums[i] <= n && nums[i] != nums[nums[i]]) {
                std::swap(nums[i], nums[nums[i]]);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (nums[i] != i)
                return i;
        }
        return n + 1;
    }
};
