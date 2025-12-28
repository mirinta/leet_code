#include <vector>

/**
 * You are given an array of integers nums of length n and a positive integer k.
 *
 * The power of an array is defined as:
 *
 * - Its maximum element if all of its elements are consecutive and sorted in ascending order.
 *
 * - -1 otherwise.
 *
 * You need to find the power of all subarrays of nums of size k.
 *
 * Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i +
 * k - 1)].
 *
 * ! 1 <= n == nums.length <= 500
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= n
 */

class Solution {
public:
    std::vector<int> resultsArray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<int> result;
        result.reserve(n - k + 1);
        for (int i = 0, count = 0; i < n; ++i) {
            if (i == 0 || nums[i] - nums[i - 1] != 1) {
                count = 1;
            } else {
                count++;
            }
            if (i >= k - 1) {
                result.push_back(count >= k ? nums[i] : -1);
            }
        }
        return result;
    }
};