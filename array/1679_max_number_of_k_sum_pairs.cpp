#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer k.
 *
 * In one operation, you can pick two numbers from the array whose sum equals k and remove them from
 * the array.
 *
 * Return the maximum number of operations you can perform on the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int maxOperations(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // time O(n), space O(n)
    int approach2(std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> freq;
        int result = 0;
        for (const auto& val : nums) {
            const int target = k - val;
            if (freq.count(target) && freq[target] > 0) {
                freq[target]--;
                result++;
            } else {
                freq[val]++;
            }
        }
        return result;
    }

    // time O(nlogn), space O(1)
    int approach1(std::vector<int>& nums, int k)
    {
        std::sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        int result = 0;
        while (left < right) {
            const int sum = nums[left] + nums[right];
            if (sum > k) {
                right--;
            } else if (sum < k) {
                left++;
            } else {
                result++;
                left++;
                right--;
            }
        }
        return result;
    }
};