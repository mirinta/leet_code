#include <vector>

/**
 * Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i,
 * j) where 0 <= i < j < n, such that nums[i] == nums[j] and (i * j) is divisible by k.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i], k <= 100
 */

class Solution {
public:
    int countPairs(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                result += nums[i] == nums[j] && (i * j % k == 0);
            }
        }
        return result;
    }
};
