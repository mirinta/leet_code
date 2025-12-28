#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * In one move, you can choose one element of nums and change it to any value.
 *
 * Return the minimum difference between the largest and smallest value of nums after performing at
 * most three moves.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minDifference(std::vector<int>& nums)
    {
        if (nums.size() <= 4)
            return 0;

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = INT_MAX;
        // case1: increase nums[0:2] to nums[3]
        result = std::min(result, nums[n - 1] - nums[3]);
        // case2: increase nums[0:1] to nums[2]
        //        decrease nums[n-1] to nums[n-2]
        result = std::min(result, nums[n - 2] - nums[2]);
        // case3: increase nums[0] to nums[1]
        //        decrease nums[n-1:n-2] to nums[n-3]
        result = std::min(result, nums[n - 3] - nums[1]);
        // case4: decrease nums[n-1:n-3] to nums[n-4]
        result = std::min(result, nums[n - 4] - nums[0]);
        return result;
    }
};