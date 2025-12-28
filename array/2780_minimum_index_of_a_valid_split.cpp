#include <unordered_map>
#include <vector>

/**
 * An element x of an integer array arr of length m is dominant if more than half the elements of
 * arr have a value of x.
 *
 * You are given a 0-indexed integer array nums of length n with one dominant element.
 *
 * You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1], but
 * the split is only valid if:
 *
 * - 0 <= i < n - 1
 *
 * - nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.
 *
 * Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j,
 * both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.
 *
 * Return the minimum index of a valid split. If no valid split exists, return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! nums has exactly one dominant element.
 */

class Solution {
public:
    int minimumIndex(std::vector<int>& nums)
    {
        const int n = nums.size();
        const auto [x, total] = findDominant(nums);
        for (int i = 0, leftCount = 0; i < n - 1; ++i) {
            leftCount += nums[i] == x;
            if (2 * leftCount > (i + 1) && 2 * (total - leftCount) > (n - i - 1))
                return i;
        }
        return -1;
    }

private:
    std::pair<int, int> findDominant(const std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        for (const auto& [val, freq] : map) {
            if (freq > nums.size() / 2)
                return {val, freq};
        }
        return {-1, -1};
    }
};
