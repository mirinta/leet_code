#include <vector>

/**
 * You are given a 0-indexed array of distinct integers nums.
 *
 * There is an element in nums that has the lowest value and an element that has the highest value. We call them the
 * minimum and maximum respectively. Your goal is to remove both these elements from the array.
 *
 * A deletion is defined as either removing an element from the front of the array or removing an element from the back
 * of the array.
 *
 * Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^5 <= nums[i] <= 10^5
 * ! The integers in nums are distinct.
 */

class Solution {
public:
    int minimumDeletions(std::vector<int>& nums)
    {
        const int n = nums.size();
        int minIdx = -1;
        int minVal = INT_MAX;
        int maxIdx = -1;
        int maxVal = INT_MIN;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > maxVal) {
                maxVal = nums[i];
                maxIdx = i;
            }
            if (nums[i] < minVal) {
                minVal = nums[i];
                minIdx = i;
            }
        }
        const int L = std::min(minIdx, maxIdx);
        const int R = std::max(minIdx, maxIdx);
        return std::min({R + 1, n - L, L + 1 + n - R});
    }
};