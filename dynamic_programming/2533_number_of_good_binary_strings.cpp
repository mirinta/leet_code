#include <vector>

/**
 * You are given four integers minLength, maxLength, oneGroup and zeroGroup.
 *
 * A binary string is good if it satisfies the following conditions:
 *
 * - The length of the string is in the range [minLength, maxLength].
 *
 * - The size of each block of consecutive 1's is a multiple of oneGroup. For example in a binary
 * string 00110111100 sizes of each block of consecutive ones are [2,4].
 *
 * - The size of each block of consecutive 0's is a multiple of zeroGroup. For example, in a binary
 * string 00110111100 sizes of each block of consecutive zeros are [2,1,2].
 *
 * Return the number of good binary strings. Since the answer may be too large, return it modulo
 * 10^9 + 7.
 *
 * Note that 0 is considered a multiple of all the numbers.
 *
 * ! 1 <= minLength <= maxLength <= 10^5
 * ! 1 <= oneGroup, zeroGroup <= maxLength
 */

class Solution {
public:
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup)
    {
        constexpr int kMod = 1e9 + 7;
        std::vector<int> dp(1 + maxLength, 0);
        dp[0] = 1;
        int result = 0;
        for (int i = 1; i <= maxLength; ++i) {
            if (i < oneGroup && i < zeroGroup)
                continue;

            if (i >= oneGroup) {
                dp[i] = (dp[i] + dp[i - oneGroup]) % kMod;
            }
            if (i >= zeroGroup) {
                dp[i] = (dp[i] + dp[i - zeroGroup]) % kMod;
            }
            if (i >= minLength) {
                result = (result + dp[i]) % kMod;
            }
        }
        return result;
    }
};