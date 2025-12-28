#include <vector>

/**
 * Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the
 * array if you can flip at most k 0's.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 * ! 0 <= k <= nums.length
 */

class Solution {
public:
    int longestOnes(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int zeros = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            zeros += 1 - nums[right];
            while (zeros > k) {
                zeros -= 1 - nums[left];
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
