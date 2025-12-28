#include <string>
#include <vector>

/**
 * A program was supposed to print an array of integers. The program forgot to print whitespaces and
 * the array is printed as a string of digits s and all we know is that all integers in the array
 * were in the range [1, k] and there are no leading zeros in the array.
 *
 * Given the string s and the integer k, return the number of the possible arrays that can be
 * printed as s using the mentioned program. Since the answer may be very large, return it modulo
 * 10^9 + 7.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of only digits and does not contain leading zeros.
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int numberOfArrays(std::string s, int k)
    {
        // dp[i] = num of possible arrays that can be printed of s[0:i-1]
        // 0 ... X j-1 j X X X X X X X i-1 i
        // |<-dp[j]->| |<-valid integer->|
        // |<-----------dp[i]----------->|
        // since k <= 1e9, we only need to consider at most 10 digits, i.e., i-j <= 10
        constexpr int kMod = 1e9 + 7;
        const int n = s.size();
        std::vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            long long val = 0;
            long long base = 1;
            for (int j = i - 1; j >= 0 && i - j <= 10; --j, base *= 10) {
                val = val + (s[j] - '0') * base;
                if (val > k)
                    break;

                if (val >= base) {
                    dp[i] = (dp[i] + dp[j]) % kMod;
                }
            }
        }
        return dp[n];
    }
};