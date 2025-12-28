#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the number of good subarrays of nums.
 *
 * A good array is an array where the number of different integers in that array is exactly k.
 *
 * - For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= nums[i], k <= nums.length
 */

class Solution {
public:
    int subarraysWithKDistinct(std::vector<int>& nums, int k)
    {
        return solve(nums, k) - solve(nums, k - 1);
    }

private:
    // num of subarrays where the num of different integers of each subarray <= k
    int solve(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            while (map.size() > k) {
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};