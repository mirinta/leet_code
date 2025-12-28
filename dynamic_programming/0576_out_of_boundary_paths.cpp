#include <cstring>

/**
 * There is an m x n grid with a ball. The ball is initially at the position [startRow,
 * startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid
 * (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the
 * ball.
 *
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move
 * the ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= m, n <= 50
 * ! 0 <= maxMove <= 50
 * ! 0 <= startRow < m
 * ! 0 <= startColumn < n
 */

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
    {
        std::memset(&memo, -1, sizeof(memo));
        return dp(startRow, startColumn, 0, m, n, maxMove);
    }

private:
    static constexpr int kMod = 1e9 + 7;
    int memo[51][51][51];

    int dp(int x, int y, int move, int m, int n, int maxMove)
    {
        if (move > maxMove)
            return 0;

        if (x < 0 || x >= m || y < 0 || y >= n)
            return 1;

        if (memo[x][y][move] != -1)
            return memo[x][y][move];

        int result = 0;
        result = (result + dp(x - 1, y, move + 1, m, n, maxMove)) % kMod;
        result = (result + dp(x + 1, y, move + 1, m, n, maxMove)) % kMod;
        result = (result + dp(x, y - 1, move + 1, m, n, maxMove)) % kMod;
        result = (result + dp(x, y + 1, move + 1, m, n, maxMove)) % kMod;
        return memo[x][y][move] = result;
    }
};