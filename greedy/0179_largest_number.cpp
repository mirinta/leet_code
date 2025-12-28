#include <algorithm>
#include <string>
#include <vector>

/**
 * Given a list of non-negative integers nums, arrange them such that they form the largest number
 * and return it.
 *
 * Since the result may be very large, so you need to return a string instead of an integer.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    std::string largestNumber(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::string> strs;
        strs.reserve(n);
        for (const auto& val : nums) {
            strs.push_back(std::to_string(val));
        }
        std::sort(strs.begin(), strs.end(), [](const auto& s1, const auto& s2) { return s1 + s2 > s2 + s1; });
        if (strs[0] == "0")
            return "0";

        std::string result;
        for (const auto& s : strs) {
            result += s;
        }
        return result;
    }
};
