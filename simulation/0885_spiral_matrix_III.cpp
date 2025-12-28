#include <vector>

/**
 * You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner
 * is at the first row and column in the grid, and the southeast corner is at the last row and
 * column.
 *
 * You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move
 * outside the grid's boundary, we continue our walk outside the grid (but may return to the grid
 * boundary later.). Eventually, we reach all rows * cols spaces of the grid.
 *
 * Return an array of coordinates representing the positions of the grid in the order you visited
 * them.
 *
 * ! 1 <= rows, cols <= 100
 * ! 0 <= rStart < rows
 * ! 0 <= cStart < cols
 */

class Solution {
public:
    std::vector<std::vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
    {
        // East, South, West, North
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        // go east, steps = 1
        // go south, steps = 1
        // go west, steps = 2
        // go north, steps = 2
        // go east, steps = 3
        // go south, steps = 3
        // go west, steps = 4
        // go north, steps = 4
        // ...
        std::vector<std::vector<int>> result;
        result.reserve(rows * cols);
        int steps = 1;
        int direction = 0;
        while (result.size() < rows * cols) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < steps; ++j) {
                    if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
                        result.push_back({rStart, cStart});
                    }
                    rStart += kDirections[direction].first;
                    cStart += kDirections[direction].second;
                }
                direction = (direction + 1) % 4;
            }
            steps++;
        }
        return result;
    }
};