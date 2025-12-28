#include <algorithm>
#include <array>
#include <map>
#include <vector>

/**
 * Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your
 * starting cell.
 *
 * From the starting cell, you can move to any other cell in the same row or column, but only if the
 * value of the destination cell is strictly greater than the value of the current cell. You can
 * repeat this process as many times as possible, moving from cell to cell until you can no longer
 * make any moves.
 *
 * Your task is to find the maximum number of cells that you can visit in the matrix by starting
 * from some cell.
 *
 * Return an integer denoting the maximum number of cells that can be visited.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! -10^5 <= mat[i][j] <= 10^5
 */

class Solution {
public:
    int maxIncreasingCells(std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<std::array<int, 3>> nums;
        nums.reserve(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                nums.push_back({mat[i][j], i, j});
            }
        }
        std::sort(nums.begin(), nums.end(), [](const auto& t1, const auto& t2) { return t1[0] < t2[0]; });
        std::vector<std::map<int, int>> dpRow(m);
        std::vector<std::map<int, int>> dpCol(n);
        int result = 0;
        for (const auto& [val, i, j] : nums) {
            int maxLength = 1;
            auto iter1 = dpRow[i].lower_bound(val);
            if (iter1 != dpRow[i].begin()) {
                maxLength = std::max(maxLength, std::prev(iter1)->second + 1);
            }
            auto iter2 = dpCol[j].lower_bound(val);
            if (iter2 != dpCol[j].begin()) {
                maxLength = std::max(maxLength, std::prev(iter2)->second + 1);
            }
            dpRow[i][val] = std::max(dpRow[i][val], maxLength);
            dpCol[j][val] = std::max(dpCol[j][val], maxLength);
            result = std::max(result, maxLength);
        }
        return result;
    }
};