#include <unordered_map>
#include <vector>

/**
 * In the town of Digitville, there was a list of numbers called nums containing integers from 0 to
 * n - 1. Each number was supposed to appear exactly once in the list, however, two mischievous
 * numbers sneaked in an additional time, making the list longer than usual.
 *
 * As the town detective, your task is to find these two sneaky numbers. Return an array of size two
 * containing the two numbers (in any order), so peace can return to Digitville.
 *
 * ! 2 <= n <= 100
 * ! nums.length == n + 2
 * ! 0 <= nums[i] < n
 * ! The input is generated such that nums contains exactly two repeated elements.
 */

class Solution
{
public:
    std::vector<int> getSneakyNumbers(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        std::vector<int> result;
        for (const auto& val : nums) {
            if (++map[val] > 1) {
                result.push_back(val);
            }
        }
        return result;
    }
};
