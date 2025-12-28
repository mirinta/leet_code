#include <array>
#include <vector>

/**
 * There is a street with n * 2 plots, where there are n plots on each side of the street. The plots
 * on each side are numbered from 1 to n. On each plot, a house can be placed.
 *
 * Return the number of ways houses can be placed such that no two houses are adjacent to each other
 * on the same side of the street. Since the answer may be very large, return it modulo 109 + 7.
 *
 * Note that if a house is placed on the ith plot on one side of the street, a house can also be
 * placed on the ith plot on the other side of the street.
 *
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int countHousePlacements(int n)
    {
        return approach2(n);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // DP with space optimization, TC = O(N), SC = O(1)
    int approach2(int n)
    {
        int noHouse = 1;
        int hasHouse = 0;
        for (int i = 1; i <= n; ++i) {
            const int backup = noHouse;
            noHouse = (backup + hasHouse) % kMod;
            hasHouse = backup;
        }
        const long long total = (noHouse + hasHouse) % kMod;
        return total * total % kMod;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(int n)
    {
        // two streets are independent
        // dp[i][0] = num of ways houses can be placed on a street with i plots while the ith plot
        // has no house dp[i][1] = num of ways houses can be placed on a street with i plots while
        // the ith plot has a house
        std::vector<std::array<int, 2>> dp(n + 1, {0, 0});
        dp[0][0] = 1;
        dp[0][1] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % kMod;
            dp[i][1] = dp[i - 1][0];
        }
        const long long total = (dp[n][0] + dp[n][1]) % kMod;
        return total * total % kMod;
    }
};