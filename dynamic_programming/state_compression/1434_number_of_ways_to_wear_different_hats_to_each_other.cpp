#include <vector>

/**
 * There are n people and 40 types of hats labeled from 1 to 40.
 *
 * Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
 *
 * Return the number of ways that the n people wear different hats to each other.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! n == hats.length
 * ! 1 <= n <= 10
 * ! 1 <= hats[i].length <= 40
 * ! 1 <= hats[i][j] <= 40
 * ! hats[i] contains a list of unique integers.
 */

class Solution {
public:
    int numberWays(std::vector<std::vector<int>>& hats)
    {
        const int n = hats.size();
        std::vector<std::vector<int>> prefer(41);
        for (int i = 0; i < n; ++i) {
            for (const auto& hat : hats[i]) {
                prefer[hat].push_back(i);
            }
        }
        std::vector<std::vector<int>> memo(41, std::vector<int>(1 << n, -1));
        return dfs(memo, 1, 0, (1 << n) - 1, prefer);
    }

private:
    int dfs(std::vector<std::vector<int>>& memo,
            int hat,
            int state,
            int target,
            const std::vector<std::vector<int>>& prefer)
    {
        if (hat == prefer.size())
            return state == target;

        if (memo[hat][state] != -1)
            return memo[hat][state];

        // case 1: skip this hat
        int result = dfs(memo, hat + 1, state, target, prefer);
        for (const auto& person : prefer[hat]) {
            if ((state >> person) & 1)
                continue; // this person already has a hat

            // case 2: this person wears this hat
            constexpr int kMod = 1e9 + 7;
            result = (result + dfs(memo, hat + 1, state | (1 << person), target, prefer)) % kMod;
        }
        return memo[hat][state] = result;
    }
};