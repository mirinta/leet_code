#include <vector>

/**
 * You are given an even number of people numPeople that stand around a circle and each person
 * shakes hands with someone else so that there are numPeople / 2 handshakes total.
 *
 * Return the number of ways these handshakes could occur such that none of the handshakes cross.
 *
 * Since the answer could be very large, return it modulo 10^9 + 7.
 *
 * ! 2 <= numPeople <= 1000
 * ! numPeople is even.
 */

class Solution {
public:
    int numberOfWays(int numPeople)
    {
        // dp[i] = num of ways to shake hands of i people
        //
        // let people 1 and j shake hands, where j = 2, 4, 6, ...
        //
        //   2 ... j-1
        // 1 --------- j
        //   i ... j+1
        //
        // the circle is divided in two parts:
        // - part 1: num of people = j-2
        // - part 2: num of people = i-j
        //
        // then, dp[i] = sum of (dp[i-j] * dp[j-2])
        constexpr int kMod = 1e9 + 7;
        std::vector<long long> dp(numPeople + 1);
        dp[0] = 1;
        for (int i = 2; i <= numPeople; i += 2) {
            for (int j = 2; j <= i; j += 2) {
                dp[i] = (dp[i] + dp[j - 2] * dp[i - j] % kMod) % kMod;
            }
        }
        return dp[numPeople];
    }
};