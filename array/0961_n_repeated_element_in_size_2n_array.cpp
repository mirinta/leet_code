#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums with the following properties:
 *
 * - nums.length == 2 * n.
 *
 * - nums contains n + 1 unique elements.
 *
 * - Exactly one element of nums is repeated n times.
 *
 * Return the element that is repeated n times.
 *
 * ! 2 <= n <= 5000
 * ! nums.length == 2 * n
 * ! 0 <= nums[i] <= 10^4
 * ! nums contains n + 1 unique elements and one of them is repeated exactly n times.
 */

class Solution {
public:
    int repeatedNTimes(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        for (int i = 0; i + 2 < n; ++i) {
            if (nums[i] == nums[i + 1] || nums[i] == nums[i + 2])
                return nums[i];
        }
        return nums[n - 1];
    }

    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size() / 2;
        std::unordered_map<int, int> map;
        for (const auto& v : nums) {
            if (++map[v] == n)
                return v;
        }
        return -1;
    }
};