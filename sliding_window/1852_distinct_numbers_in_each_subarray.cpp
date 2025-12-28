#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, you are asked to construct the array ans of size
 * n-k+1 where ans[i] is the number of distinct numbers in the subarray nums[i:i+k-1] = [nums[i],
 * nums[i+1], ..., nums[i+k-1]].
 *
 * Return the array ans.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    std::vector<int> distinctNumbers(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        std::vector<int> result;
        result.reserve(n - k + 1);
        for (int left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            if (right >= k) {
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            if (right >= k - 1) {
                result.emplace_back(map.size());
            }
        }
        return result;
    }
};