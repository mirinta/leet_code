#include <vector>

/**
 * Given the integers zero, one, low, and high, we can construct a string by starting with an empty
 * string, and then at each step perform either of the following:
 *
 * - Append the character '0' zero times.
 *
 * - Append the character '1' one times.
 *
 * This can be performed any number of times.
 *
 * A good string is a string constructed by the above process having a length between low and high
 * (inclusive).
 *
 * Return the number of different good strings that can be constructed satisfying these properties.
 * Since the answer can be large, return it modulo 10^9 + 7.
 *
 * ! 1 <= low <= high <= 10^5
 * ! 1 <= zero, one <= low
 */

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one)
    {
        static constexpr int kMod = 1e9 + 7;
        // dp[i] = num of good strings of length i
        std::vector<int> dp(high + 1, 0);
        dp[0] = 1;
        int result = 0;
        for (int i = 1; i <= high; ++i) {
            if (i < zero && i < one)
                continue;

            if (i >= zero) {
                dp[i] = (dp[i] + dp[i - zero]) % kMod;
            }
            if (i >= one) {
                dp[i] = (dp[i] + dp[i - one]) % kMod;
            }
            if (i >= low) {
                result = (result + dp[i]) % kMod;
            }
        }
        return result;
    }
};
