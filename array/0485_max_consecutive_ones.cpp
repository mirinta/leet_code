#include <vector>

/**
 * Given a binary array "nums", return the maximum number of consecutive "1"'s in the array.
 */

class Solution {
public:
    int findMaxConsecutiveOnes(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int result = 0;
        int count = 0;
        for (const auto& i : nums) {
            count = i == 1 ? count + 1 : 0;
            result = std::max(result, count);
        }
        return result;
    }
};