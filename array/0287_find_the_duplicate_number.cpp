#include <algorithm>
#include <unordered_set>
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
        return approach3(nums);
    }

private:
    // time O(n), space O(1)
    int approach3(std::vector<int>& nums)
    {
        // indicies are pigeonholes, and elements are pigeon IDs
        // given nums[i] = j and i!=j, we need to put pigeon j into pigeonhole j
        // if pigeonhole j is not empty, then j is the duplicate number
        for (int pigeonhole = 0; pigeonhole < nums.size(); ++pigeonhole) {
            const int pigeonID = std::abs(nums[pigeonhole]);
            if (nums[pigeonID] < 0)
                return pigeonID;

            nums[pigeonID] *= -1;
        }
        return -1;
    }

    // sort, time O(nlogn), space (depends on implementation)
    int approach2(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] == nums[i + 1])
                return nums[i];
        }
        return -1;
    }

    // hash set, time O(n), space O(n)
    int approach1(const std::vector<int>& nums)
    {
        std::unordered_set<int> set;
        for (const auto& val : nums) {
            if (set.count(val))
                return val;

            set.insert(val);
        }
        return -1;
    }
};
