#include <array>
#include <vector>

/**
 * An attendance record for a student can be represented as a string where each character signifies
 * whether the student was absent, late, or present on that day. The record only contains the
 * following three characters:
 *
 * - 'A': Absent.
 *
 * - 'L': Late.
 *
 * - 'P': Present.
 *
 * Any student is eligible for an attendance award if they meet both of the following criteria:
 *
 * - The student was absent ('A') for strictly fewer than 2 days total.
 *
 * - The student was never late ('L') for 3 or more consecutive days.
 *
 * Given an integer n, return the number of possible attendance records of length n that make a
 * student eligible for an attendance award. The answer may be very large, so return it modulo 10^9
 * + 7.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    int checkRecord(int n)
    {
        // dp[i][j][k] = num of valid records of i days that
        // there are exactly j 'Absent's and
        // there are exactly k consecutive 'Late's at the end
        constexpr int kMod = 1e9 + 7;
        std::vector<std::array<std::array<int, 3>, 2>> dp(n + 1);
        dp[0][0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            // case 1: the ith day is a 'Present'
            for (int j = 0; j <= 1; ++j) {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0]) % kMod;
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][1]) % kMod;
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][2]) % kMod;
            }
            // case 2: the ith day is an 'Absent'
            dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][0]) % kMod;
            dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][1]) % kMod;
            dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][2]) % kMod;
            // case 3: the ith day is a 'Late'
            for (int j = 0; j <= 1; ++j) {
                dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][0]) % kMod;
                dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j][1]) % kMod;
            }
        }
        int result = 0;
        for (int j = 0; j <= 1; ++j) {
            for (int k = 0; k <= 2; ++k) {
                result = (result + dp[n][j][k]) % kMod;
            }
        }
        return result;
    }
};