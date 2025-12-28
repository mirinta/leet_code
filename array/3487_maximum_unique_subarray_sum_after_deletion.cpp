#include <climits>
#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * You are allowed to delete any number of elements from nums without making it empty. After
 * performing the deletions, select a subarray of nums such that:
 *
 * 1. All elements in the subarray are unique.
 *
 * 2. The sum of the elements in the subarray is maximized.
 *
 * Return the maximum sum of such a subarray.
 *
 * ! 1 <= nums.length <= 100
 * ! -100 <= nums[i] <= 100
 */

class Solution {
public:
    int maxSum(std::vector<int>& nums)
    {
        int max = INT_MIN;
        std::unordered_set<int> set;
        int sum = 0;
        for (const auto& val : nums) {
            max = std::max(max, val);
            if (set.count(val) || val < 0)
                continue;

            sum += val;
            set.insert(val);
        }
        return max < 0 ? max : sum;
    }
};
