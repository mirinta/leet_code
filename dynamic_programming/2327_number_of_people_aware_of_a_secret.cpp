#include <vector>

/**
 * On day 1, one person discovers a secret.
 *
 * You are given an integer delay, which means that each person will share the secret with a new
 * person every day, starting from delay days after discovering the secret. You are also given an
 * integer forget, which means that each person will forget the secret forget days after discovering
 * it. A person cannot share the secret on the same day they forgot it, or on any day afterwards.
 *
 * Given an integer n, return the number of people who know the secret at the end of day n. Since
 * the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 2 <= n <= 1000
 * ! 1 <= delay < forget <= n
 */

class Solution
{
public:
    int peopleAwareOfSecret(int n, int delay, int forget)
    {
        static constexpr int kMod = 1e9 + 7;
        std::vector<int> dp(n + 1,
                            0); // num of new people aware of the secret at the end of ith day
        std::vector<int> diff(n + 1, 0); // diff[i] = dp[i] - dp[i-1]
        diff[1] = 1;
        diff[2] = -1;
        for (int i = 1; i <= n; ++i) {
            dp[i] = (diff[i] + dp[i - 1]) % kMod;
            if (i + delay <= n) {
                diff[i + delay] = (diff[i + delay] + dp[i]) % kMod;
            }
            if (i + forget <= n) {
                diff[i + forget] = (diff[i + forget] - dp[i] + kMod) % kMod;
            }
        }
        int result = 0;
        for (int i = n - forget + 1; i <= n; ++i) {
            result = (result + dp[i]) % kMod;
        }
        return result;
    }
};