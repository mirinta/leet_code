#include <vector>

/**
 * There is a group of n members, and a list of various crimes they could commit. The ith crime
 * generates a profit[i] and requires group[i] members to participate in it. If a member
 * participates in one crime, that member can't participate in another crime.
 *
 * Let's call a profitable scheme any subset of these crimes that generates at least minProfit
 * profit, and the total number of members participating in that subset of crimes is at most n.
 *
 * Return the number of schemes that can be chosen. Since the answer may be very large, return it
 * modulo 10^9 + 7.
 *
 * ! 1 <= n <= 100
 * ! 0 <= minProfit <= 100
 * ! 1 <= group.length <= 100
 * ! 1 <= group[i] <= 100
 * ! profit.length == group.length
 * ! 0 <= profit[i] <= 100
 */

class Solution {
public:
    int profitableSchemes(int n, int minProfit, std::vector<int>& group, std::vector<int>& profit)
    {
        const int m = group.size();
        memo.resize(m, std::vector<std::vector<int>>(n + 1, std::vector<int>(minProfit + 1, -1)));
        return dfs(0, 0, 0, n, minProfit, group, profit);
    }

private:
    static constexpr int kMod = 1e9 + 7;
    std::vector<std::vector<std::vector<int>>> memo;

    int dfs(int i,
            int members,
            int gain,
            int n,
            int minProfit,
            const std::vector<int>& group,
            const std::vector<int>& profit)
    {
        if (i == group.size())
            return gain >= minProfit;

        if (memo[i][members][gain] != -1)
            return memo[i][members][gain];

        int result = dfs(i + 1, members, gain, n, minProfit, group, profit);
        if (members + group[i] <= n) {
            result = (result + dfs(i + 1, members + group[i], std::min(gain + profit[i], minProfit), n, minProfit,
                                   group, profit)) %
                     kMod;
        }
        return memo[i][members][gain] = result;
    }
};