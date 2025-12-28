#include <vector>

/**
 * You are given a 0-indexed integer array nums. A subarray s of length m is called alternating if:
 *
 * - m is greater than 1.
 *
 * - s1 = s0 + 1.
 *
 * - The 0-indexed subarray s looks like [s0, s1, s0, s1,...,s(m-1) % 2]. In other words, s1 - s0 =
 * 1, s2 - s1 = -1, s3 - s2 = 1, s4 - s3 = -1, and so on up to s[m - 1] - s[m - 2] = (-1)^m.
 *
 * Return the maximum length of all alternating subarrays present in nums or -1 if no such subarray
 * exists.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int alternatingSubarray(std::vector<int>& nums)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                const int m = j - i + 1;
                const int diff = m % 2 == 0 ? 1 : -1;
                if (nums[j] - nums[j - 1] != diff)
                    break;

                result = std::max(result, m);
            }
        }
        return result == 0 ? -1 : result;
    }
};