#include <vector>

/**
 * Given a binary array nums, you should delete one element from it.
 *
 * Return the size of the longest non-empty subarray containing only 1's in the resulting array.
 * Return 0 if there is no such subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution {
public:
    int longestSubarray(std::vector<int>& nums)
    {
        // find the longest subarray nums[j:i] with at most one 0
        // if there's exactly one 0, answer = L-1
        // otherwise, answer = std::min(n-1, L), because there must be one deleted element
        const int n = nums.size();
        int zeros = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            zeros += 1 - nums[right];
            while (zeros > 1) {
                zeros -= 1 - nums[left];
                left++;
            }
            result = std::max(result, std::min(n - 1, right - left + 1 - zeros));
        }
        return result;
    }
};