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
 * ! 1 <= n == nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= indexDifference <= 10^5
 * ! 0 <= valueDifference <= 10^9
 */

class Solution {
public:
    std::vector<int> findIndices(std::vector<int>& nums, int indexDifference, int valueDifference)
    {
        const int n = nums.size();
        int minIdx = -1;
        int maxIdx = -1;
        int maxVal = INT_MIN;
        int minVal = INT_MAX;
        for (int i = 0; i < n; ++i) {
            const int j = i - indexDifference;
            if (j < 0 || j >= n)
                continue;

            if (nums[j] > maxVal) {
                maxVal = nums[j];
                maxIdx = j;
            }
            if (nums[j] < minVal) {
                minVal = nums[j];
                minIdx = j;
            }
            if (nums[i] - minVal >= valueDifference)
                return {minIdx, i};

            if (maxVal - nums[i] >= valueDifference)
                return {maxIdx, i};
        }
        return {-1, -1};
    }
};