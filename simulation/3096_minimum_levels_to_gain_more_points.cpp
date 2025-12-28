#include <vector>

/**
 * You are given a binary array possible of length n.
 *
 * Danielchandg and Bob are playing a game that consists of n levels. Some of the levels in the game
 * are impossible to clear while others can always be cleared. In particular, if possible[i] == 0,
 * then the ith level is impossible to clear for both the players. A player gains 1 point on
 * clearing a level and loses 1 point if the player fails to clear it.
 *
 * At the start of the game, Danielchandg will play some levels in the given order starting from the
 * 0th level, after which Bob will play for the rest of the levels.
 *
 * Danielchandg wants to know the minimum number of levels he should play to gain more points than
 * Bob, if both players play optimally to maximize their points.
 *
 * Return the minimum number of levels danielchandg should play to gain more points. If this is not
 * possible, return -1.
 *
 * Note that each player must play at least 1 level.
 *
 * ! 2 <= n == possible.length <= 10^5
 * ! possible[i] is either 0 or 1.
 */

class Solution {
public:
    int minimumLevels(std::vector<int>& possible)
    {
        const int n = possible.size();
        int total = 0;
        for (const auto& val : possible) {
            total += val == 0 ? -1 : 1;
        }
        int score = 0;
        for (int i = 0; i < n - 1; ++i) {
            score += possible[i] == 0 ? -1 : 1;
            if (score > total - score)
                return i + 1;
        }
        return -1;
    }
};