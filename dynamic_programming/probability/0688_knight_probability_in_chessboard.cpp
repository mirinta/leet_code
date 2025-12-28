#include <vector>

/**
 * On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k
 * moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right
 * cell is (n - 1, n - 1).
 *
 * A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells
 * in a cardinal direction, then one cell in an orthogonal direction.
 *
 * Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even
 * if the piece would go off the chessboard) and moves there.
 *
 * The knight continues moving until it has made exactly k moves or has moved off the chessboard.
 *
 * Return the probability that the knight remains on the board after it has stopped moving.
 *
 * ! 1 <= n <= 25
 * ! 0 <= k <= 100
 * ! 0 <= row, column <= n - 1
 */

class Solution {
public:
    double knightProbability(int n, int k, int row, int column)
    {
        return approach2(n, k, row, column);
    }

private:
    static constexpr double P = 0.125; // 1/8
    static const std::vector<std::pair<int, int>> kDirections;

    // DP with space optimization, TC = (KN^2), SC = O(N^2)
    double approach2(int n, int k, int row, int column)
    {
        std::vector<std::vector<double>> dp(n, std::vector<double>(n));
        dp[row][column] = 1;
        auto prev = dp;
        for (int t = 1; t <= k; ++t) {
            prev.assign(dp.begin(), dp.end());
            std::fill(dp.begin(), dp.end(), std::vector<double>(n, 0));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (const auto& [dx, dy] : kDirections) {
                        const int x = i + dx;
                        const int y = j + dy;
                        if (x < 0 || x >= n || y < 0 || y >= n)
                            continue;

                        dp[i][j] += prev[x][y] * P;
                    }
                }
            }
        }
        double result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result += dp[i][j];
            }
        }
        return result;
    }

    // DP, TC = O(KN^2), SC = O(KN^2)
    double approach1(int n, int k, int row, int column)
    {
        // dp[t][i][j] = probability that the knight is located at (i,j) after exactly t moves
        std::vector<std::vector<std::vector<double>>> dp(k + 1,
                                                         std::vector<std::vector<double>>(n, std::vector<double>(n)));
        dp[0][row][column] = 1;
        for (int t = 1; t <= k; ++t) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    for (const auto& [dx, dy] : kDirections) {
                        const int x = i + dx;
                        const int y = j + dy;
                        if (x < 0 || x >= n || y < 0 || y >= n)
                            continue;

                        dp[t][i][j] += dp[t - 1][x][y] * P;
                    }
                }
            }
        }
        double result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result += dp[k][i][j];
            }
        }
        return result;
    }
};

const std::vector<std::pair<int, int>> Solution::kDirections{{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                                             {2, -1},  {2, 1},  {1, -2},  {1, 2}};