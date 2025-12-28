#include <unordered_map>
#include <vector>

/**
 * You are given an array nums, where each number in the array appears either once or twice.
 *
 * Return the bitwise XOR of all the numbers that appear twice in the array, or 0 if no number
 * appears twice.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 * ! Each number in nums appears either once or twice.
 */

class Solution {
public:
    int duplicateNumbersXOR(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        int result = 0;
        for (const auto& [val, freq] : map) {
            if (freq == 2) {
                result ^= val;
            }
        }
        return result;
    }
};