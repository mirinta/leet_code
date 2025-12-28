#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given a 0-indexed n x integer matrix "grid", return the number of pairs (r_i, c_i) such that row
 * r_i and column c_i are equal.
 *
 * A row and column pair is considered equal if they contain the same elements in the same order
 * (i.e., an equal array).
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 200
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    int equalPairs(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::unordered_map<std::string, int> map;
        for (const auto& rowValues : grid) {
            std::string row;
            for (const auto& val : rowValues) {
                row.append(std::to_string(val));
                row.push_back(',');
            }
            map[row]++;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            std::string col;
            for (int j = 0; j < n; ++j) {
                col.append(std::to_string(grid[j][i]));
                col.push_back(',');
            }
            if (map.count(col)) {
                result += map[col];
            }
        }
        return result;
    }
};