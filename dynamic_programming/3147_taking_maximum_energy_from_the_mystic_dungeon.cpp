#include <vector>

/**
 * In a mystic dungeon, n magicians are standing in a line. Each magician has an attribute that
 * gives you energy. Some magicians can give you negative energy, which means taking energy from
 * you.
 *
 * You have been cursed in such a way that after absorbing energy from magician i, you will be
 * instantly transported to magician (i + k). This process will be repeated until you reach the
 * magician where (i + k) does not exist.
 *
 * In other words, you will choose a starting point and then teleport with k jumps until you reach
 * the end of the magicians' sequence, absorbing all the energy during the journey.
 *
 * You are given an array energy and an integer k. Return the maximum possible energy you can gain.
 *
 * ! 1 <= energy.length <= 10^5
 * ! -1000 <= energy[i] <= 1000
 * ! 1 <= k <= energy.length - 1
 */

class Solution {
public:
    int maximumEnergy(std::vector<int>& energy, int k)
    {
        const int n = energy.size();
        std::vector<int> memo(n, INT_MIN);
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, dfs(memo, i, k, energy));
        }
        return result;
    }

private:
    int dfs(std::vector<int>& memo, int i, int k, const std::vector<int>& energy)
    {
        if (i >= energy.size())
            return 0;

        if (memo[i] != INT_MIN)
            return memo[i];

        return memo[i] = energy[i] + dfs(memo, i + k, k, energy);
    }
};