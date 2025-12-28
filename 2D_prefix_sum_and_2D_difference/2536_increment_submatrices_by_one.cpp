#include <vector>

/**
 * You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer
 * matrix mat filled with zeroes.
 *
 * You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i],
 * you should do the following operation:
 *
 * - Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom
 * right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <=
 * y <= col2i.
 *
 * Return the matrix mat after performing every query.
 *
 * ! 1 <= n <= 500
 * ! 1 <= queries.length <= 10^4
 * ! 0 <= row1i <= row2i < n
 * ! 0 <= col1i <= col2i < n
 */

class Solution {
public:
    std::vector<std::vector<int>> rangeAddQueries(int n, std::vector<std::vector<int>>& queries)
    {
        // diff[i][j] = x, it means we increase all elements of the submatrix
        // of mat[i:n-1][j:n-1] by x
        std::vector<std::vector<int>> diff(n + 1, std::vector<int>(n + 1, 0));
        for (const auto& query : queries) {
            const int row1 = query[0];
            const int col1 = query[1];
            const int row2 = query[2];
            const int col2 = query[3];
            diff[row1][col1] += 1;
            diff[row2 + 1][col1] -= 1;
            diff[row1][col2 + 1] -= 1;
            diff[row2 + 1][col2 + 1] += 1;
        }
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (j > 0) {
                    diff[i][j] += diff[i][j - 1];
                }
                if (i > 0) {
                    diff[i][j] += diff[i - 1][j];
                }
                if (i > 0 && j > 0) {
                    diff[i][j] -= diff[i - 1][j - 1];
                }
            }
        }
        diff.pop_back();
        for (auto& row : diff) {
            row.pop_back();
        }
        return diff;
    }
};