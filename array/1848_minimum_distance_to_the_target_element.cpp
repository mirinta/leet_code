#include <climits>
#include <vector>

/**
 * Given an integer array nums (0-indexed) and two integers target and start, find an index i such that nums[i] ==
 * target and abs(i - start) is minimized. Note that abs(x) is the absolute value of x.
 *
 * Return abs(i - start).
 *
 * It is guaranteed that target exists in nums.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^4
 * ! 0 <= start < nums.length
 * ! target is in nums.
 */

class Solution {
public:
    int getMinDistance(std::vector<int>& nums, int target, int start)
    {
        const int n = nums.size();
        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (nums[i] != target)
                continue;

            result = std::min(result, std::abs(i - start));
        }
        return result;
    }
};
