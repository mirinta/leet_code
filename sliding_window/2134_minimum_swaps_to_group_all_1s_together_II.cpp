#include <numeric>
#include <vector>

/**
 * A swap is defined as taking two distinct positions in an array and swapping the values in them.
 *
 * A circular array is defined as an array where we consider the first element and the last element
 * to be adjacent.
 *
 * Given a binary circular array nums, return the minimum number of swaps required to group all 1's
 * present in the array together at any location.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution {
public:
    int minSwaps(std::vector<int>& nums)
    {
        // fixed size sliding window
        // window size = num of ones that need to be grouped together within nums
        // if a sliding window contains #ones 1's,
        // then #operations = #zeros within the sliding window
        const int n = nums.size();
        const int ones = std::accumulate(nums.begin(), nums.end(), 0);
        int result = INT_MAX;
        for (int left = 0, right = 0, zeros = 0; right < 2 * n; ++right) {
            zeros += 1 - nums[right % n];
            while (right - left + 1 > ones) {
                zeros -= 1 - nums[left % n];
                left++;
            }
            if (right - left + 1 == ones) {
                result = std::min(result, zeros);
            }
        }
        return result;
    }
};
