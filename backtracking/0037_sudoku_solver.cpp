#include <vector>

/**
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * A sudoku solution must satisfy all of the following rules:
 *
 * - Each of the digits 1-9 must occur exactly once in each row.
 *
 * - Each of the digits 1-9 must occur exactly once in each column.
 *
 * - Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 *
 * The '.' character indicates empty cells.
 *
 * ! board.length == 9
 * ! board[i].length == 9
 * ! board[i][j] is a digit or '.'.
 * ! It is guaranteed that the input board has only one solution.
 */

class Solution {
public:
    void solveSudoku(std::vector<std::vector<char>>& board)
    {
        backtrack(board, 0, 0);
    }

private:
    static constexpr int m = 9; // rows
    static constexpr int n = 9; // cols

    bool isValid(char val, int i, int j, const std::vector<std::vector<char>>& board)
    {
        for (int row = 0; row < m; ++row) {
            if (board[row][j] == val)
                return false;
        }
        for (int col = 0; col < n; ++col) {
            if (board[i][col] == val)
                return false;
        }
        const int offsetX = (i / 3) * 3;
        const int offsetY = (j / 3) * 3;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[row + offsetX][col + offsetY] == val)
                    return false;
            }
        }
        return true;
    }

    bool backtrack(std::vector<std::vector<char>>& board, int i, int j)
    {
        if (i == m)
            return true; // problem solved

        if (j == n)
            return backtrack(board, i + 1, 0);

        if (board[i][j] != '.')
            return backtrack(board, i, j + 1);

        for (char x = '1'; x <= '9'; ++x) {
            if (isValid(x, i, j, board)) {
                board[i][j] = x;
                if (backtrack(board, i, j + 1))
                    return true;

                board[i][j] = '.';
            }
        }
        return false;
    }
};