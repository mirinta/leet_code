#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
 * connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are
 * surrounded by water.
 *
 * An island is considered to be the same as another if and only if one island can be translated
 * (and not rotated or reflected) to equal the other.
 *
 * Return the number of distinct islands.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 50
 * ! grid[i][j] is either 0 or 1.
 */

class Solution {
public:
    int numDistinctIslands(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        visited.resize(m, std::vector<bool>(n, false));
        uniqueSignatures.clear();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == kLand && !visited[i][j]) {
                    visited[i][j] = true;
                    std::string signature;
                    dfs(signature, i, j, grid);
                    uniqueSignatures.insert(std::move(signature));
                }
            }
        }
        return uniqueSignatures.size();
    }

private:
    static constexpr int kLand = 1;
    const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<std::vector<bool>> visited;
    std::unordered_set<std::string> uniqueSignatures;

    void dfs(std::string& signature, int x, int y, const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        for (int d = 0; d < kDirections.size(); ++d) {
            const auto& [dx, dy] = kDirections[d];
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (visited[i][j] || grid[i][j] != kLand)
                continue;

            visited[i][j] = true;
            signature.push_back('0' + d); // 0 for up, 1 for down, 2 for left, 3 for right
            dfs(signature, i, j, grid);
        }
        signature.push_back('|');
    }
};