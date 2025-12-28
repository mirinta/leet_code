#include <vector>

/**
 * A competition consists of n players numbered from 0 to n - 1.
 *
 * You are given an integer array skills of size n and a positive integer k, where skills[i] is the
 * skill level of player i. All integers in skills are unique.
 *
 * All players are standing in a queue in order from player 0 to player n - 1.
 *
 * The competition process is as follows:
 *
 * - The first two players in the queue play a game, and the player with the higher skill level
 * wins.
 *
 * - After the game, the winner stays at the beginning of the queue, and the loser goes to the end
 * of it. The winner of the competition is the first player who wins k games in a row.
 *
 * Return the initial index of the winning player.
 *
 * ! n == skills.length
 * ! 2 <= n <= 10^5
 * ! 1 <= k <= 10^9
 * ! 1 <= skills[i] <= 10^6
 * ! All integers in skills are unique.
 */

class Solution {
public:
    int findWinningPlayer(std::vector<int>& skills, int k)
    {
        // ... p i ......... j
        //     |<-k players->|
        //
        // if player i can win k games in a row, then nums[i] = max of nums[p:j]
        // if p is on the left side of nums[i], then nums[p] = max of nums[0:i-1]
        // thus, nums[i] = max of nums[0:j]
        const int n = skills.size();
        int maxIndex = 0;
        for (int i = 1, win = 0; i < n; ++i) {
            if (skills[i] > skills[maxIndex]) {
                maxIndex = i;
                win = 0;
            }
            if (++win == k)
                break;
        }
        return maxIndex;
    }
};