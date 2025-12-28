#include <vector>

/**
 * You are given two integer arrays, skill and mana, of length n and m, respectively.
 *
 * In a laboratory, n wizards must brew m potions in order. Each potion has a mana capacity mana[j]
 * and must pass through all the wizards sequentially to be brewed properly. The time taken by the
 * ith wizard on the jth potion is timeij = skill[i] * mana[j].
 *
 * Since the brewing process is delicate, a potion must be passed to the next wizard immediately
 * after the current wizard completes their work. This means the timing must be synchronized so that
 * each wizard begins working on a potion exactly when it arrives. ​
 *
 * Return the minimum amount of time required for the potions to be brewed properly.
 *
 * ! n == skill.length
 * ! m == mana.length
 * ! 1 <= n, m <= 5000
 * ! 1 <= mana[i], skill[i] <= 5000
 */

class Solution {
public:
    long long minTime(std::vector<int>& skill, std::vector<int>& mana)
    {
        // dp[i][j] = min time for the jth wizard to finish brewing the ith potion
        const int n = skill.size();
        const int m = mana.size();
        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]) + mana[i - 1] * skill[j - 1];
            }
            for (int j = n - 1; j >= 1; --j) {
                dp[i][j] = dp[i][j + 1] - mana[i - 1] * skill[j];
            }
        }
        return dp[m][n];
    }
};
