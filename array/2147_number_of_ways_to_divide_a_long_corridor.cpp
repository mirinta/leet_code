#include <array>
#include <string>
#include <vector>

/**
 * Along a long library corridor, there is a line of seats and decorative plants. You are given a
 * 0-indexed string corridor of length n consisting of letters 'S' and 'P' where each 'S' represents
 * a seat and each 'P' represents a plant.
 *
 * One room divider has already been installed to the left of index 0, and another to the right of
 * index n - 1. Additional room dividers can be installed. For each position between indices i - 1
 * and i (1 <= i <= n - 1), at most one divider can be installed.
 *
 * Divide the corridor into non-overlapping sections, where each section has exactly two seats with
 * any number of plants. There may be multiple ways to perform the division. Two ways are different
 * if there is a position with a room divider installed in the first way but not in the second way.
 *
 * Return the number of ways to divide the corridor. Since the answer may be very large, return it
 * modulo 10^9 + 7. If there is no way, return 0.
 *
 * ! n == corridor.length
 * ! 1 <= n <= 10^5
 * ! corridor[i] is either 'S' or 'P'.
 */

class Solution
{
public:
    int numberOfWays(const std::string& corridor) { return approach2(corridor); }

private:
    static constexpr long long kMod = 1e9 + 7;

    int approach2(const std::string& corridor)
    {
        // dp[i][j] = num of ways to divide corridor[0:i-1]
        // and the last section has exactly j seats
        const int n = corridor.size();
        std::vector<std::array<long long, 3>> dp(n + 1, {0, 0, 0});
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (corridor[i - 1] == 'S') {
                dp[i][0] = 0;
                dp[i][1] = (dp[i - 1][2] + dp[i - 1][0]) % kMod;
                dp[i][2] = dp[i - 1][1];
            } else {
                dp[i][0] = (dp[i - 1][0] + dp[i - 1][2]) % kMod;
                dp[i][1] = dp[i - 1][1];
                dp[i][2] = dp[i - 1][2];
            }
        }
        return dp[n][2];
    }

    int approach1(const std::string& corridor)
    {
        const int n = corridor.size();
        std::vector<int> seats; // indices
        for (int i = 0; i < n; ++i) {
            if (corridor[i] == 'S') {
                seats.push_back(i);
            }
        }
        if (seats.empty() || seats.size() % 2)
            return 0;

        long long result = 1;
        for (int i = 0; i < seats.size(); i += 2) {
            const long long choices = i == 0 ? 1 : (seats[i] - seats[i - 1]);
            result = result * choices % kMod;
        }
        return result;
    }
};