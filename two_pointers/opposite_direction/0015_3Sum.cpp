#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums", return all the triplets "nums[i], nums[j], nums[k]" such that
 * "i != j, j != k", and "nums[i] + nums[j] + nums[k] == 0".
 *
 * ! 3 <= nums.length <= 3000
 * ! -10^5 <= nums[i] <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        for (int i = 0; i + 2 < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue; // skip duplicates

            if (nums[i] + nums[i + 1] + nums[i + 2] > 0)
                break; // no way to find nums[j] and nums[k]

            if (nums[i] + nums[n - 2] + nums[n - 1] < 0)
                continue; // try larger nums[i]

            const int target = -nums[i];
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                const int sum = nums[left] + nums[right];
                if (sum > target) {
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++; // skip duplicates
                    }
                    right--;
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--; // skip duplicates
                    }
                }
            }
        }
        return result;
    }
};
