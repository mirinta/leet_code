#include <string>
#include <vector>

/**
 * The n-queens puzzle is the problem of placing "n" queens on an "n x n" chessboard such that no
 * two queens attack each other.
 *
 * Given an integer "n", return all distinct solutions to the n-queens puzzle. You may return the
 * answer in any order.
 *
 * Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and
 * '.' both indicate a queen and an empty space, respectively.
 *
 * ! 1 <= n <= 9
 */

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        std::vector<std::string> grid(n, std::string(n, '.'));
        std::vector<std::vector<std::string>> result;
        backtrack(result, grid, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<std::string>>& result, std::vector<std::string>& grid, int i, int n)
    {
        if (i == n) {
            result.push_back(grid);
            return;
        }
        for (int j = 0; j < n; ++j) {
            if (!isValid(i, j, grid))
                continue;

            grid[i][j] = 'Q';
            backtrack(result, grid, i + 1, n);
            grid[i][j] = '.';
        }
    }

    bool isValid(int row, int col, const std::vector<std::string>& grid)
    {
        for (int i = row - 1, offset = 1; i >= 0; --i, ++offset) {
            if (grid[i][col] == 'Q')
                return false;

            if (col + offset < grid.size() && grid[i][col + offset] == 'Q')
                return false;

            if (col - offset >= 0 && grid[i][col - offset] == 'Q')
                return false;
        }
        return true;
    }
};