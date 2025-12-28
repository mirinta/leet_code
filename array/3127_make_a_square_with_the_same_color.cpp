#include <vector>

/**
 * You are given a 2D matrix grid of size 3 x 3 consisting only of characters 'B' and 'W'. Character
 * 'W' represents the white color, and character 'B' represents the black color.
 *
 * Your task is to change the color of at most one cell so that the matrix has a 2 x 2 square where
 * all cells are of the same color.
 *
 * Return true if it is possible to create a 2 x 2 square of the same color, otherwise, return
 * false.
 *
 * ! grid.length == 3
 * !grid[i].length == 3
 * !grid[i][j] is either 'W' or 'B'.
 */

class Solution {
public:
    bool canMakeSquare(std::vector<std::vector<char>>& grid)
    {
        return isValid(0, 0, grid) || isValid(0, 1, grid) || isValid(1, 0, grid) || isValid(1, 1, grid);
    }

private:
    bool isValid(int x, int y, const std::vector<std::vector<char>>& grid)
    {
        int result = grid[x][y] == 'B';
        result += grid[x][y + 1] == 'B';
        result += grid[x + 1][y] == 'B';
        result += grid[x + 1][y + 1] == 'B';
        return result != 2;
    }
};