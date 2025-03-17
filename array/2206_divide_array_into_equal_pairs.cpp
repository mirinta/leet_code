#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums consisting of 2 * n integers.
 *
 * You need to divide nums into n pairs such that:
 *
 * - Each element belongs to exactly one pair.
 *
 * - The elements present in a pair are equal.
 *
 * Return true if nums can be divided into n pairs, otherwise return false.
 *
 * ! nums.length == 2 * n
 * ! 1 <= n <= 500
 * ! 1 <= nums[i] <= 500
 */

class Solution
{
public:
    bool divideArray(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        for (const auto& [val, count] : map) {
            if (count % 2)
                return false;
        }
        return true;
    }
};
