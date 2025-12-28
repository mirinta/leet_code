#include <set>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer x.
 *
 * Find the minimum absolute difference between two elements in the array that are at least x
 * indices apart.
 *
 * In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is
 * minimized.
 *
 * Return an integer denoting the minimum absolute difference between two elements that are at least
 * x indices apart.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= x < nums.length
 */

class Solution {
public:
    int minAbsoluteDifference(std::vector<int>& nums, int x)
    {
        const int n = nums.size();
        std::set<int> set;
        int result = INT_MAX;
        for (int j = x; j < n; ++j) {
            set.insert(nums[j - x]);
            if (auto iter = set.lower_bound(nums[j]); iter != set.end()) {
                result = std::min(result, *iter - nums[j]);
            }
            if (auto iter = set.upper_bound(nums[j]); iter != set.begin()) {
                result = std::min(result, nums[j] - *std::prev(iter));
            }
            if (result == 0)
                break;
        }
        return result;
    }
};