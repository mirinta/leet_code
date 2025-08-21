#include <vector>

/**
 * Given an integer array nums, return the number of subarrays filled with 0.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution
{
public:
    long long zeroFilledSubarray(std::vector<int>& nums)
    {
        // if a subarray with length L is filled with 0,
        // then there are 1+2+...+L = (1+L)*L/2 valid subarrays
        const int n = nums.size();
        int i = 0;
        long long count = 0;
        long long result = 0;
        while (i < n) {
            int j = i;
            while (j < n && nums[j] == 0) {
                j++;
            }
            count = j - i;
            result += (1 + count) * count / 2;
            i = std::max(i + 1, j);
        }
        return result;
    }
};
