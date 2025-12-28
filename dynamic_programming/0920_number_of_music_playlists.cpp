#include <vector>

/**
 * Your music player contains n different songs. You want to listen to goal songs (not necessarily
 * different) during your trip. To avoid boredom, you will create a playlist so that:
 *
 * - Every song is played at least once.
 *
 * - A song can only be played again only if k other songs have been played.
 *
 * Given n, goal, and k, return the number of possible playlists that you can create. Since the
 * answer can be very large, return it modulo 10^9 + 7.
 *
 * ! 0 <= k < n <= goal <= 100
 */

class Solution {
public:
    int numMusicPlaylists(int n, int goal, int k)
    {
        return approach3(n, goal, k);
    }

private:
    using LL = long long;
    static constexpr int kMod = 1e9 + 7;

    // DP with space optimization, TC = O(NG), SC = (N)
    int approach3(int n, int goal, int k)
    {
        std::vector<LL> dp(n + 1, 0);
        for (int i = 1; i <= goal; ++i) {
            dp[0] = i == 1;
            for (int j = n; j >= 1; --j) {
                const LL case1 = dp[j - 1] * (n - j + 1) % kMod;
                const LL case2 = dp[j] * std::max(j - k, 0) % kMod;
                dp[j] = (case1 + case2) % kMod;
            }
        }
        return dp[n];
    }

    // DP (bottom-up), TC = O(NG), SC = O(NG)
    int approach1(int n, int goal, int k)
    {
        // dp[i][j] = num of ways to make a playlist with i songs that has j unique songs
        std::vector<std::vector<LL>> dp(goal + 1, std::vector<LL>(n + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= goal; ++i) {
            for (int j = 1; j <= n; ++j) {
                // case 1: choose a new song
                const LL case1 = dp[i - 1][j - 1] * (n - j + 1) % kMod;
                // case 2: choose an old song
                // suppose the playlist is {1,2,3,4}
                // if k = 0, options of the 5th song = {1,2,3,4}
                // if k = 1, options of the 5th song = {1,2,3}
                // if k = 2, options of the 5th song = {1,2}
                // if k = 3, options of the 5th song = {1}
                // if k >= 4, options of the 5th song = {}
                const LL case2 = dp[i - 1][j] * std::max(j - k, 0) % kMod;
                dp[i][j] = (case1 + case2) % kMod;
            }
        }
        return dp[goal][n];
    }

    // DP (top-down), TC = O(NG), SC = O(NG)
    int approach2(int n, int goal, int k)
    {
        std::vector<std::vector<LL>> memo(goal, std::vector<LL>(n + 1, -1));
        return dfs(memo, 0, 0, n, goal, k);
    }

    int dfs(std::vector<std::vector<LL>>& memo, LL i, LL played, LL n, LL goal, LL k)
    {
        if (i == goal)
            return played == n;

        if (memo[i][played] != -1)
            return memo[i][played];

        int result = 0;
        if (n > played) {
            result = (result + (n - played) * dfs(memo, i + 1, played + 1, n, goal, k)) % kMod;
        }
        if (played > k) {
            result = (result + (played - k) * dfs(memo, i + 1, played, n, goal, k)) % kMod;
        }
        return memo[i][played] = result;
    }
};