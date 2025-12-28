#include <vector>

/**
 * You are given a 0-indexed m x n binary matrix land where a 0 represents a hectare of forested
 * land and a 1 represents a hectare of farmland.
 *
 * To keep the land organized, there are designated rectangular areas of hectares that consist
 * entirely of farmland. These rectangular areas are called groups. No two groups are adjacent,
 * meaning farmland in one group is not four-directionally adjacent to another farmland in a
 * different group.
 *
 * land can be represented by a coordinate system where the top left corner of land is (0, 0) and
 * the bottom right corner of land is (m-1, n-1). Find the coordinates of the top left and bottom
 * right corner of each group of farmland. A group of farmland with a top left corner at (r1, c1)
 * and a bottom right corner at (r2, c2) is represented by the 4-length array [r1, c1, r2, c2].
 *
 * Return a 2D array containing the 4-length arrays described above for each group of farmland in
 * land. If there are no groups of farmland, return an empty array. You may return the answer in any
 * order.
 *
 * ! m == land.length
 * ! n == land[i].length
 * ! 1 <= m, n <= 300
 * ! land consists of only 0's and 1's.
 * ! Groups of farmland are rectangular in shape.
 */

class Solution {
public:
    std::vector<std::vector<int>> findFarmland(std::vector<std::vector<int>>& land)
    {
        const int m = land.size();
        const int n = land[0].size();
        std::vector<std::vector<int>> result;
        for (int r1 = 0; r1 < m; ++r1) {
            for (int c1 = 0; c1 < n; ++c1) {
                if (land[r1][c1] == 1) {
                    int r2 = r1;
                    int c2 = c1;
                    dfs(land, r2, c2, r1, c1);
                    result.push_back({r1, c1, r2, c2});
                }
            }
        }
        return result;
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    void dfs(std::vector<std::vector<int>>& land, int& r2, int& c2, int r1, int c1)
    {
        const int m = land.size();
        const int n = land[0].size();
        r2 = std::max(r2, r1);
        c2 = std::max(c2, c1);
        land[r1][c1] = 0;
        for (const auto& [dx, dy] : kDirections) {
            const int i = r1 + dx;
            const int j = c1 + dy;
            if (i < 0 || i >= m || j < 0 || j >= n || land[i][j] != 1)
                continue;

            dfs(land, r2, c2, i, j);
        }
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};