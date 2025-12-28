#include <vector>

/**
 * Given an array of integers nums containing n + 1 integers where each integer is in the range [1,
 * n] inclusive.
 *
 * There is only one repeated number in nums, return this repeated number.
 *
 * You must solve the problem without modifying the array nums and uses only constant extra space.
 *
 * ! 1 <= n <= 10^5
 * ! nums.length == n + 1
 * ! 1 <= nums[i] <= n
 * ! All the integers in nums appear only once except for precisely one integer which appears two or
 * ! more times.
 */

class Solution {
public:
    int findDuplicate(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }

    int approach1(std::vector<int>& nums)
    {
        const int n = nums.size();
        for (int i = 0; i < n; ++i) {
            const int pigeon = std::abs(nums[i]);
            if (nums[pigeon] < 0)
                return pigeon;

            nums[pigeon] *= -1;
        }
        return -1;
    }
};