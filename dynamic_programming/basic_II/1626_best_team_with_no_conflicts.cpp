#include <algorithm>
#include <vector>

/**
 * You are the manager of a basketball team. For the upcoming tournament, you want to choose the
 * team with the highest overall score. The score of the team is the sum of scores of all the
 * players in the team.
 *
 * However, the basketball team is not allowed to have conflicts. A conflict exists if a younger
 * player has a strictly higher score than an older player. A conflict does not occur between
 * players of the same age.
 *
 * Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age
 * of the ith player, respectively, return the highest overall score of all possible basketball
 * teams.
 *
 * ! 1 <= scores.length, ages.length <= 1000
 * ! scores.length == ages.length
 * ! 1 <= scores[i] <= 10^6
 * ! 1 <= ages[i] <= 1000
 */

class Solution {
public:
    int bestTeamScore(std::vector<int>& scores, std::vector<int>& ages)
    {
        const int n = scores.size();
        std::vector<std::pair<int, int>> players(n); // <score, age>
        for (int i = 0; i < n; ++i) {
            players[i].first = scores[i];
            players[i].second = ages[i];
        }
        // dp[i] = max score of the subsequence of players[0:i] ending at players[i]
        std::sort(players.begin(), players.end());
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].first;
            for (int j = i - 1; j >= 0; --j) {
                if (players[i].second >= players[j].second) {
                    dp[i] = std::max(dp[i], players[i].first + dp[j]);
                }
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};