#include <vector>

/**
 * Given an integer array nums, return the largest integer that only occurs once. If no integer
 * occurs once, return -1.
 *
 * ! 1 <= nums.length <= 2000
 * ! 0 <= nums[i] <= 1000
 */

class Solution {
public:
    int largestUniqueNumber(std::vector<int>& nums)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        std::vector<int> count(max + 1, 0);
        for (const auto& val : nums) {
            count[val]++;
        }
        for (int i = max; i >= 1; --i) {
            if (count[i] == 1)
                return i;
        }
        return -1;
    }
};
