#include <array>
#include <queue>
#include <vector>

/**
 * In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at
 * (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by
 * ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
 *
 * In one move the snake can:
 *
 * - Move one cell to the right if there are no blocked cells there. This move keeps the
 * horizontal/vertical position of the snake as it is.
 *
 * - Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical
 * position of the snake as it is.
 *
 * - Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In
 * that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
 *
 * - Rotate counterclockwise if it's in a vertical position and the two cells to its right are both
 * empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
 *
 * Return the minimum number of moves to reach the target.
 *
 * If there is no way to reach the target, return -1.
 *
 * ! 2 <= n <= 100
 * ! 0 <= grid[i][j] <= 1
 * ! It is guaranteed that the snake starts at empty cells.
 */

class Solution {
public:
    int minimumMoves(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<std::array<int, 2>>> visited(n, std::vector<std::array<int, 2>>(n));
        visited[0][0][0] = true;
        // <tailX, tailY, 0 (horizontal) or 1 (vertical)>
        std::queue<std::tuple<int, int, int>> queue;
        queue.emplace(0, 0, 0);
        int moves = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [tailX, tailY, orientation] = queue.front();
                queue.pop();
                if (tailX == n - 1 && tailY == n - 2 && orientation == 0)
                    return moves;

                // go right
                if (isValidBody(tailX, tailY + 1, orientation, grid) && !visited[tailX][tailY + 1][orientation]) {
                    visited[tailX][tailY + 1][orientation] = true;
                    queue.emplace(tailX, tailY + 1, orientation);
                }
                // go down
                if (isValidBody(tailX + 1, tailY, orientation, grid) && !visited[tailX + 1][tailY][orientation]) {
                    visited[tailX + 1][tailY][orientation] = true;
                    queue.emplace(tailX + 1, tailY, orientation);
                }
                // rotate clockwise or counterclockwise
                if (isValidBody(tailX, tailY, orientation ^ 1, grid) && isValidPos(tailX + 1, tailY + 1, grid) &&
                    !visited[tailX][tailY][orientation ^ 1]) {
                    visited[tailX][tailY][orientation ^ 1] = true;
                    queue.emplace(tailX, tailY, orientation ^ 1);
                }
            }
            moves++;
        }
        return -1;
    }

private:
    bool isValidPos(int x, int y, const std::vector<std::vector<int>>& grid)
    {
        return x >= 0 && x < grid.size() && y >= 0 && y < grid.size() && grid[x][y] == 0;
    }

    bool isValidBody(int tailX, int tailY, int orientation, const std::vector<std::vector<int>>& grid)
    {
        return isValidPos(tailX, tailY, grid) && isValidPos(tailX + orientation, tailY + 1 - orientation, grid);
    }
};