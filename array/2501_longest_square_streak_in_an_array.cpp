#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums. A subsequence of nums is called a square streak if:
 *
 * - The length of the subsequence is at least 2, and
 *
 * - after sorting the subsequence, each element (except the first element) is the square of the
 * previous number.
 *
 * Return the length of the longest square streak in nums, or return -1 if there is no square
 * streak.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 2 <= nums[i] <= 10^5
 */

class Solution {
public:
    int longestSquareStreak(std::vector<int>& nums)
    {
        std::unordered_set<long long> set(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : set) {
            long long curr = val;
            int count = 1;
            while (set.count(curr * curr)) {
                count++;
                curr *= curr;
            }
            result = std::max(result, count);
        }
        return result < 2 ? -1 : result;
    }
};