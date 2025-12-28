#include <vector>

/**
 * Given an array "nums". We define a running sum of an array as "runningSum[i] =
 * sum(nums[0]...nums[i])".
 *
 * Return the running sum of "nums".
 */

class Solution {
public:
    std::vector<int> runningSum(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::vector<int> result(nums.size(), nums.front());
        for (size_t i = 1; i < nums.size(); ++i) {
            result[i] = nums[i] + result[i - 1];
        }
        return result;
    }
};