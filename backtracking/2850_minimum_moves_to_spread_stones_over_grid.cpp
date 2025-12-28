#include <array>
#include <tuple>
#include <vector>

/**
 * You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones
 * in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single
 * cell.
 *
 * In one move, you can move a single stone from its current cell to any other cell if the two cells
 * share a side.
 *
 * Return the minimum number of moves required to place one stone in each cell.
 *
 * ! grid.length == grid[i].length == 3
 * ! 0 <= grid[i][j] <= 9
 * ! Sum of grid is equal to 9.
 */

class Solution {
public:
    int minimumMoves(std::vector<std::vector<int>>& grid)
    {
        std::vector<Pair> zeros;
        std::vector<Tuple> ones;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == 0) {
                    zeros.emplace_back(i, j);
                } else if (grid[i][j] > 1) {
                    ones.emplace_back(i, j, grid[i][j]);
                }
            }
        }
        if (zeros.empty())
            return 0;

        int result = INT_MAX;
        backtrack(result, ones, 0, 0, zeros);
        return result;
    }

private:
    using Pair = std::pair<int, int>;
    using Tuple = std::tuple<int, int, int>;

    void backtrack(int& result, std::vector<Tuple>& ones, int i, int moves, std::vector<Pair>& zeros)
    {
        if (i == zeros.size()) {
            result = std::min(result, moves);
            return;
        }
        const auto& [x0, y0] = zeros[i];
        for (auto& [x, y, count] : ones) {
            if (count <= 1)
                continue;

            count--;
            backtrack(result, ones, i + 1, moves + std::abs(x - x0) + std::abs(y - y0), zeros);
            count++;
        }
    }
};