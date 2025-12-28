#include <unordered_map>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * Return the total frequencies of elements in nums such that those elements all have the maximum
 * frequency.
 *
 * The frequency of an element is the number of occurrences of that element in the array.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int maxFrequencyElements(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        int maxFreq = 0;
        for (const auto& val : nums) {
            map[val]++;
            maxFreq = std::max(maxFreq, map[val]);
        }
        int result = 0;
        for (const auto& [val, freq] : map) {
            if (freq == maxFreq) {
                result += freq;
            }
        }
        return result;
    }
};