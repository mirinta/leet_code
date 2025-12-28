#include <vector>

/**
 * There is an m x n cake that needs to be cut into 1 x 1 pieces.
 *
 * You are given integers m, n, and two arrays:
 *
 * - horizontalCut of size m - 1, where horizontalCut[i] represents the cost to cut along the
 * horizontal line i.
 *
 * - verticalCut of size n - 1, where verticalCut[j] represents the cost to cut along the
 * vertical line j.
 *
 * In one operation, you can choose any piece of cake that is not yet a 1 x 1 square and perform one
 * of the following cuts:
 *
 * 1. Cut along a horizontal line i at a cost of horizontalCut[i].
 *
 * 2. Cut along a vertical line j at a cost of verticalCut[j].
 *
 * After the cut, the piece of cake is divided into two distinct pieces.
 *
 * The cost of a cut depends only on the initial cost of the line and does not change.
 *
 * Return the minimum total cost to cut the entire cake into 1 x 1 pieces.
 *
 * ! 1 <= m, n <= 20
 * ! horizontalCut.length == m - 1
 * ! verticalCut.length == n - 1
 * ! 1 <= horizontalCut[i], verticalCut[i] <= 10^3
 */

class Solution {
public:
    int minimumCost(int m, int n, std::vector<int>& horizontalCut, std::vector<int>& verticalCut)
    {
        std::memset(memo, -1, sizeof(memo));
        return dfs(0, 0, m, n, horizontalCut, verticalCut);
    }

private:
    int memo[21][21][21][21];

    // top left corner = (x0, y0)
    // bottom right corner = (x1, y1)
    int dfs(int x0, int y0, int x1, int y1, const std::vector<int>& horizontalCut, const std::vector<int>& verticalCut)
    {
        if (x0 + 1 == x1 && y0 + 1 == y1)
            return 0;

        if (memo[x0][y0][x1][y1] != -1)
            return memo[x0][y0][x1][y1];

        int result = INT_MAX;
        for (int i = x0 + 1; i < x1; ++i) {
            int cost = horizontalCut[i - 1];
            cost += dfs(x0, y0, i, y1, horizontalCut, verticalCut);
            cost += dfs(i, y0, x1, y1, horizontalCut, verticalCut);
            result = std::min(result, cost);
        }
        for (int j = y0 + 1; j < y1; ++j) {
            int cost = verticalCut[j - 1];
            cost += dfs(x0, y0, x1, j, horizontalCut, verticalCut);
            cost += dfs(x0, j, x1, y1, horizontalCut, verticalCut);
            result = std::min(result, cost);
        }
        return memo[x0][y0][x1][y1] = result;
    }
};