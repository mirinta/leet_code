#include <algorithm>
#include <vector>

/**
 * Alice and Bob take turns playing a game, with Alice starting first.
 *
 * There are n stones in a pile. On each player's turn, they can remove a stone from the pile and
 * receive points based on the stone's value. Alice and Bob may value the stones differently.
 *
 * You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and
 * bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
 *
 * The winner is the person with the most points after all the stones are chosen. If both players
 * have the same amount of points, the game results in a draw. Both players will play optimally.
 * Both players know the other's values.
 *
 * Determine the result of the game, and:
 *
 * - If Alice wins, return 1.
 *
 * - If Bob wins, return -1.
 *
 * - If the game results in a draw, return 0.
 *
 * ! n == aliceValues.length == bobValues.length
 * ! 1 <= n <= 10^5
 * ! 1 <= aliceValues[i], bobValues[i] <= 100
 */

class Solution {
public:
    int stoneGameVI(std::vector<int>& aliceValues, std::vector<int>& bobValues)
    {
        // if player X picks the ith pile,
        // he gets pileX[i] score and his opponent can't get pileY[i] score
        // thus, the profit of picking the ith pile = pileX[i] + pileY[i]
        // the optimal strategy of each player is picking the pile with maximum profit
        const int n = aliceValues.size();
        std::vector<std::pair<int, int>> pairs; // <profit, i>
        pairs.reserve(n);
        for (int i = 0; i < n; ++i) {
            pairs.emplace_back(aliceValues[i] + bobValues[i], i);
        }
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2) { return p1.first > p2.first; });
        int alice = 0;
        int bob = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                alice += aliceValues[pairs[i].second];
            } else {
                bob += bobValues[pairs[i].second];
            }
        }
        if (alice == bob)
            return 0;

        return alice > bob ? 1 : -1;
    }
};