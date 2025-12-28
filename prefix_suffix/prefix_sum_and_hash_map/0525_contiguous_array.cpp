#include <unordered_map>
#include <vector>

/**
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal
 * number of 0 and 1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution {
public:
    int findMaxLength(std::vector<int>& nums)
    {
        // let presum[i] = sum of nums[0:i]
        // if nums[j+1:i] is a valid subarray, then
        // 2 * (presum[i] - presum[j]) = i - j
        // 2 * presum[i] - i = 2 * presum[j] - j
        const int n = nums.size();
        // base case: nums[0:i+1] is valid
        // 2 * presum[i] = i + 1
        // 2 * presum[i] - i = 1;
        std::unordered_map<int, int> map;
        map[1] = -1;
        int sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            const int target = 2 * sum - i;
            if (map.count(target)) {
                result = std::max(result, i - map[target]);
            } else {
                map[target] = i;
            }
        }
        return result;
    }
};