#include <vector>

/**
 * Given two positive integers m and n which are the height and width of a 0-indexed 2D-array board,
 * a pair of positive integers (r, c) which is the starting position of the knight on the board.
 *
 * Your task is to find an order of movements for the knight, in a manner that every cell of the
 * board gets visited exactly once (the starting cell is considered visited and you shouldn't visit
 * it again).
 *
 * Return the array board in which the cells' values show the order of visiting the cell starting
 * from 0 (the initial place of the knight).
 *
 * Note that a knight can move from cell (r1, c1) to cell (r2, c2) if 0 <= r2 <= m - 1 and 0 <= c2
 * <= n - 1 and min(abs(r1 - r2), abs(c1 - c2)) = 1 and max(abs(r1 - r2), abs(c1 - c2)) = 2.
 *
 * ! 1 <= m, n <= 5
 * ! 0 <= r <= m - 1
 * ! 0 <= c <= n - 1
 * ! The inputs will be generated such that there exists at least one possible order of movements
 * ! with the given condition
 */

class Solution {
public:
    std::vector<std::vector<int>> tourOfKnight(int m, int n, int r, int c)
    {
        std::vector<std::vector<int>> result(m, std::vector<int>(n, -1));
        result[r][c] = 0;
        backtrack(result, r, c, 1, m, n);
        return result;
    }

private:
    bool backtrack(std::vector<std::vector<int>>& result, int i, int j, int count, int m, int n)
    {
        if (count == m * n)
            return true;

        static const std::vector<std::pair<int, int>> kDirections{{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                                                                  {1, 2},   {2, 1},   {2, -1}, {1, -2}};
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || y < 0 || x >= m || y >= n || result[x][y] != -1)
                continue;

            result[x][y] = count;
            if (backtrack(result, x, y, count + 1, m, n))
                return true;

            result[x][y] = -1;
        }
        return false;
    }
};