#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array nums consisting of positive integers. You can choose two indices
 * i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of
 * nums[j].
 *
 * Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and
 * j that satisfy the conditions.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int maximumSum(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        int result = -1;
        for (const auto& val : nums) {
            const int target = digitSum(val);
            if (map.count(target)) {
                result = std::max(result, val + map[target]);
            }
            map[target] = std::max(map[target], val);
        }
        return result;
    }

private:
    int digitSum(int val)
    {
        int result = 0;
        while (val) {
            result += val % 10;
            val /= 10;
        }
        return result;
    }
};
