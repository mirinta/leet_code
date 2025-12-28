#include <unordered_set>

/**
 * You are given a 0-indexed integer array nums.
 *
 * The distinct count of a subarray of nums is defined as:
 *
 * Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i
 * <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count
 * of nums[i..j]. Return the sum of the squares of distinct counts of all subarrays of nums.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    int sumCounts(std::vector<int>& nums)
    {
        int result = 0;
        std::unordered_set<int> set;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i; j < nums.size(); ++j) {
                set.insert(nums[j]);
                result += set.size() * set.size();
            }
            set.clear();
        }
        return result;
    }
};