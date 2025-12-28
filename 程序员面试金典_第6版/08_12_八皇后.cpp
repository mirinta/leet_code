#include <string>
#include <vector>

/**
 * 设计一种算法，打印 N 皇后在 N × N
 * 棋盘上的各种摆法，其中每个皇后都不同行、不同列，也不在对角线上。这里的“对角线”指的是所有的对角线，不只是平分整个棋盘的那两条对角线。
 *
 * 注意：本题相对原题做了扩展
 */

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n)
    {
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> grid(n, std::string(n, '.'));
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
            if (!isValid(grid, i, j, n))
                continue;

            grid[i][j] = 'Q';
            backtrack(result, grid, i + 1, n);
            grid[i][j] = '.';
        }
    }

    bool isValid(const std::vector<std::string>& grid, int row, int j, int n)
    {
        // ?    ?    ?
        //   ?  ?  ?
        //      j
        for (int i = row - 1, offset = 1; i >= 0; --i, ++offset) {
            if (grid[i][j] == 'Q')
                return false;

            if (j - offset >= 0 && grid[i][j - offset] == 'Q')
                return false;

            if (j + offset < n && grid[i][j + offset] == 'Q')
                return false;
        }
        return true;
    }
};