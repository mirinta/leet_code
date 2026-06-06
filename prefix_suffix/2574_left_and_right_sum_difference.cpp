#include <numeric>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of size n.
 *
 * Define two arrays leftSum and rightSum where:
 *
 * - leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element,
 * leftSum[i] = 0.
 *
 * - rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element,
 * rightSum[i] = 0.
 *
 * Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    std::vector<int> leftRightDifference(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        std::vector<int> result(n, 0);
        for (int i = 0, left = 0; i < n; ++i) {
            result[i] = std::abs(total - left - nums[i] - left);
            left += nums[i];
        }
        return result;
    }
};