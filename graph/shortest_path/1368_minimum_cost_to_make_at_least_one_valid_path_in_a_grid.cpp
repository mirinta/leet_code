#include <queue>
#include <tuple>
#include <vector>

/**
 * Given an m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit
 * if you are currently in this cell. The sign of grid[i][j] can be:
 *
 * - 1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
 *
 * - 2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
 *
 * - 3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
 *
 * - 4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
 *
 * Notice that there could be some signs on the cells of the grid that point outside the grid.
 *
 * You will initially start at the upper left cell (0, 0). A valid path in the grid is a path that
 * starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1) following
 * the signs on the grid. The valid path does not have to be the shortest.
 *
 * You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.
 *
 * Return the minimum cost to make the grid have at least one valid path.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 100
 * ! 1 <= grid[i][j] <= 4
 */

class Solution {
public:
    int minCost(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        using Tuple = std::tuple<int, int, int>; // <cost, x, y>
        auto comparator = [](const Tuple& t1, const Tuple& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator);
        pq.emplace(0, 0, 0);
        std::vector<std::vector<int>> costTo(m, std::vector<int>(n, INT_MAX));
        costTo[0][0] = 0;
        while (!pq.empty()) {
            const auto [cost, x, y] = pq.top();
            pq.pop();
            if (cost > costTo[x][y])
                continue;

            if (x == m - 1 && y == n - 1)
                return cost;

            for (int d = 1; d <= 4; ++d) {
                const auto& [dx, dy] = kDirections[d - 1];
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                const int newCost = (d != grid[x][y]) + cost;
                if (newCost < costTo[i][j]) {
                    pq.emplace(newCost, i, j);
                    costTo[i][j] = newCost;
                }
            }
        }
        return -1;
    }
};