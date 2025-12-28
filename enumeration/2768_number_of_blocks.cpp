#include <unordered_map>
#include <vector>

/**
 * You are given two integers m and n representing the dimensions of a 0-indexed m x n grid.
 *
 * You are also given a 0-indexed 2D integer matrix coordinates, where coordinates[i] = [x, y]
 * indicates that the cell with coordinates [x, y] is colored black. All cells in the grid that do
 * not appear in coordinates are white.
 *
 * A block is defined as a 2 x 2 submatrix of the grid. More formally, a block with cell [x, y] as
 * its top-left corner where 0 <= x < m - 1 and 0 <= y < n - 1 contains the coordinates [x, y], [x +
 * 1, y], [x, y + 1], and [x + 1, y + 1].
 *
 * Return a 0-indexed integer array arr of size 5 such that arr[i] is the number of blocks that
 * contains exactly i black cells.
 *
 * ! 2 <= m <= 10^5
 * ! 2 <= n <= 10^5
 * ! 0 <= coordinates.length <= 10^4
 * ! coordinates[i].length == 2
 * ! 0 <= coordinates[i][0] < m
 * ! 0 <= coordinates[i][1] < n
 * ! It is guaranteed that coordinates contains pairwise distinct coordinates.
 */

class Solution {
public:
    std::vector<long long> countBlackBlocks(int m, int n, std::vector<std::vector<int>>& coordinates)
    {
        // use top-left of a 2x2 block as its identifier (I), a black cell is denoted as B
        // I(B) X | I  B | I  X | I  X
        // X    X | X  X | B  X | X  B
        // NOTE: top-left of a block can't exist in the last row and the last column of the grid
        auto encode = [n](long long x, long long y) { return x * n + y; };
        std::unordered_map<long long, long long> map;
        static const std::vector<std::pair<long long, long long>> kDirections{{0, 0}, {0, -1}, {-1, 0}, {-1, -1}};
        for (const auto& coordinate : coordinates) {
            const auto& x = coordinate[0];
            const auto& y = coordinate[1];
            for (const auto& [dx, dy] : kDirections) {
                const auto i = x + dx;
                const auto j = y + dy;
                if (i >= 0 && i < m - 1 && j >= 0 && j < n - 1) {
                    map[encode(i, j)] += 1;
                }
            }
        }
        std::vector<long long> result(5, 0);
        long long numOfBlocksContainsBlack = 0;
        for (const auto& [_, val] : map) {
            result[val]++;
            numOfBlocksContainsBlack++;
        }
        // there're (m-1)(n-1) 2x2 blocks in a mxn grid
        result[0] = static_cast<long long>(m - 1) * (n - 1) - numOfBlocksContainsBlack;
        return result;
    }
};