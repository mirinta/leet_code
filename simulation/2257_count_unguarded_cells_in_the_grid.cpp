#include <vector>

/**
 * You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D
 * integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj]
 * represent the positions of the ith guard and jth wall respectively.
 *
 * A guard can see every cell in the four cardinal directions (north, east, south, or west) starting
 * from their position unless obstructed by a wall or another guard. A cell is guarded if there is
 * at least one guard that can see it.
 *
 * Return the number of unoccupied cells that are not guarded.
 *
 * ! 1 <= m, n <= 10^5
 * ! 2 <= m * n <= 10^5
 * ! 1 <= guards.length, walls.length <= 5 * 10^4
 * ! 2 <= guards.length + walls.length <= m * n
 * ! guards[i].length == walls[j].length == 2
 * ! 0 <= rowi, rowj < m
 * ! 0 <= coli, colj < n
 * ! All the positions in guards and walls are unique.
 */

class Solution {
public:
    int countUnguarded(int m, int n, std::vector<std::vector<int>>& guards, std::vector<std::vector<int>>& walls)
    {
        std::vector<std::vector<char>> grid(m, std::vector<char>(n, ' '));
        for (const auto& coord : walls) {
            grid[coord[0]][coord[1]] = 'W';
        }
        for (const auto& coord : guards) {
            grid[coord[0]][coord[1]] = 'G';
        }
        for (const auto& coord : guards) {
            const int row = coord[0];
            const int col = coord[1];
            for (int i = row - 1; i >= 0; --i) {
                if (grid[i][col] == 'W' || grid[i][col] == 'G')
                    break;

                grid[i][col] = 'V';
            }
            for (int i = row + 1; i < m; ++i) {
                if (grid[i][col] == 'W' || grid[i][col] == 'G')
                    break;

                grid[i][col] = 'V';
            }
            for (int j = col - 1; j >= 0; --j) {
                if (grid[row][j] == 'W' || grid[row][j] == 'G')
                    break;

                grid[row][j] = 'V';
            }
            for (int j = col + 1; j < n; ++j) {
                if (grid[row][j] == 'W' || grid[row][j] == 'G')
                    break;

                grid[row][j] = 'V';
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result += grid[i][j] == ' ';
            }
        }
        return result;
    }
};