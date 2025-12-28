#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array players, where players[i] represents the ability of the
 * ith player. You are also given a 0-indexed integer array trainers, where trainers[j] represents
 * the training capacity of the jth trainer.
 *
 * The ith player can match with the jth trainer if the player's ability is less than or equal to
 * the trainer's training capacity. Additionally, the ith player can be matched with at most one
 * trainer, and the jth trainer can be matched with at most one player.
 *
 * Return the maximum number of matchings between players and trainers that satisfy these
 * conditions.
 *
 * ! 1 <= players.length, trainers.length <= 10^5
 * ! 1 <= players[i], trainers[j] <= 10^9
 *
 * ! This question is the same as LC.445
 */

class Solution {
public:
    int matchPlayersAndTrainers(std::vector<int>& players, std::vector<int>& trainers)
    {
        const int n = players.size();
        const int m = trainers.size();
        std::sort(players.begin(), players.end());
        std::sort(trainers.begin(), trainers.end());
        int result = 0;
        for (int i = m - 1, j = n - 1; i >= 0 && j >= 0; --i, --j) {
            while (j >= 0 && players[j] > trainers[i]) {
                j--;
            }
            result += j >= 0;
        }
        return result;
    }
};