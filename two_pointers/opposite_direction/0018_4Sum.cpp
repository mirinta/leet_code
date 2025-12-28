#include <algorithm>
#include <vector>

/**
 * Given an array "nums" of "n" integers, return an array of all the unique quadruplets "nums[a],
 * nums[b], nums[c], nums[d]" such that:
 *
 * - 0 <= a, b, c, d < n
 *
 * - a, b, c and d are distinct
 *
 * - nums[a] + nums[b] + nums[c] + nums[d] = target
 *
 * You may return the answer in any order.
 *
 * ! 1 <= nums.length <= 200
 * ! -10^9 <= nums[i] <= 10^9
 * ! -10^9 <= target <= 10^9
 */

class Solution {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        for (int i = 0; i + 3 < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue; // skip duplicates

            if ((long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break; // no way to find nums[j], nums[k] and nums[p]

            if ((long long)nums[i] + nums[n - 1] + nums[n - 2] + nums[n - 3] < target)
                continue; // try larger nums[i]

            // same as the 3Sum problem (LC.15)
            for (int j = i + 1; j + 2 < n; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue; // skip duplicates

                if ((long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                    break; // no way to find nums[k] and nums[p]

                if ((long long)nums[i] + nums[j] + nums[n - 1] + nums[n - 2] < target)
                    continue; // try larger nums[j]

                int left = j + 1;
                int right = n - 1;
                while (left < right) {
                    const long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum > target) {
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});
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
        }
        return result;
    }
};
