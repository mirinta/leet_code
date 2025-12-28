#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j and
 * j - i != nums[j] - nums[i].
 *
 * Return the total number of bad pairs in nums.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long countBadPairs(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result += i - map[i - nums[i]];
            map[i - nums[i]]++;
        }
        return result;
    }
};