#include <vector>

/**
 * You are given a 0-indexed integer array nums having length n, an integer indexDifference, and an
 * integer valueDifference.
 *
 * Your task is to find two indices i and j, both in the range [0, n - 1], that satisfy the
 * following conditions:
 *
 * - abs(i - j) >= indexDifference, and
 *
 * - abs(nums[i] - nums[j]) >= valueDifference
 *
 * Return an integer array answer, where answer = [i, j] if there are two such indices, and answer =
 * [-1, -1] otherwise. If there are multiple choices for the two indices, return any of them.
 *
 * Note: i and j may be equal.
 *
 * ! 1 <= n == nums.length <= 100
 * ! 0 <= nums[i] <= 50
 * ! 0 <= indexDifference <= 100
 * ! 0 <= valueDifference <= 50
 */

class Solution {
public:
    std::vector<int> findIndices(std::vector<int>& nums, int indexDifference, int valueDifference)
    {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + indexDifference; j < nums.size(); ++j) {
                if (std::abs(nums[i] - nums[j]) >= valueDifference)
                    return {i, j};
            }
        }
        return {-1, -1};
    }
};