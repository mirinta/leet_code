#include <vector>

/**
 * Given an m x n matrix "board" containing "X" and "O", capture all regions that are
 * 4-directionally surrounded by "X".
 *
 * A region is captured by flipping all "O"'s into "X"s in that surrounded region.
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 1 <= m, n <= 200
 * ! board[i][j] is 'X' or 'O'.
 */

class Solution {
public:
    void solve(std::vector<std::vector<char>>& board)
    {
        const int m = board.size();
        const int n = board[0].size();
        // step1: change all 'O's that are connected to the 'O's on the border to '#'
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') {
                dfs(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                dfs(board, i, n - 1);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (board[0][j] == 'O') {
                dfs(board, 0, j);
            }
            if (board[m - 1][j] == 'O') {
                dfs(board, m - 1, j);
            }
        }
        // step2: change each 'O' to 'X', and change each '#' to 'O'
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == '#') {
                    board[i][j] = 'O';
                }
            }
        }
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(std::vector<std::vector<char>>& board, int x, int y)
    {
        const int m = board.size();
        const int n = board[0].size();
        board[x][y] = '#';
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (board[i][j] == 'O') {
                dfs(board, i, j);
            }
        }
    }
};