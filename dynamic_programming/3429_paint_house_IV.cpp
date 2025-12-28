#include <array>
#include <climits>
#include <vector>

/**
 * You are given an even integer n representing the number of houses arranged in a straight line,
 * and a 2D array cost of size n x 3, where cost[i][j] represents the cost of painting house i with
 * color j + 1.
 *
 * The houses will look beautiful if they satisfy the following conditions:
 *
 * - No two adjacent houses are painted the same color.
 *
 * - Houses equidistant from the ends of the row are not painted the same color. For example, if n =
 * 6, houses at positions (0, 5), (1, 4), and (2, 3) are considered equidistant.
 *
 * Return the minimum cost to paint the houses such that they look beautiful.
 *
 * ! 2 <= n <= 10^5
 * ! n is even.
 * ! cost.length == n
 * ! cost[i].length == 3
 * ! 0 <= cost[i][j] <= 10^5
 */

class Solution {
public:
    long long minCost(int n, std::vector<std::vector<int>>& cost)
    {
        Memo memo(n / 2, std::array<std::array<long long, 4>, 4>{
                             {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}}});
        return dfs(memo, n / 2 - 1, 3, 3, cost);
    }

private:
    using Memo = std::vector<std::array<std::array<long long, 4>, 4>>;

    // X X X X index .......... equidistant_index X X X X
    //           <-|            |->
    long long dfs(Memo& memo, int index, int prevColor, int prevEquidColor, const std::vector<std::vector<int>>& cost)
    {
        if (index < 0)
            return 0;

        if (memo[index][prevColor][prevEquidColor] != -1)
            return memo[index][prevColor][prevEquidColor];

        const int equidIndex = cost.size() - index - 1;
        long long result = LLONG_MAX;
        for (int color = 0; color < 3; ++color) {
            if (color == prevColor)
                continue;

            for (int equidColor = 0; equidColor < 3; ++equidColor) {
                if (equidColor == color || equidColor == prevEquidColor)
                    continue;

                result = std::min(result, cost[index][color] + cost[equidIndex][equidColor] +
                                              dfs(memo, index - 1, color, equidColor, cost));
            }
        }
        return memo[index][prevColor][prevEquidColor] = result;
    }
};
