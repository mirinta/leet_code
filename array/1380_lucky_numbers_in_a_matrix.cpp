#include <vector>

/**
 * Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
 *
 * A lucky number is an element of the matrix such that it is the minimum element in its row and
 * maximum in its column.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= n, m <= 50
 * ! 1 <= matrix[i][j] <= 10^5.
 * ! All elements in the matrix are distinct.
 */

class Solution {
public:
    std::vector<int> luckyNumbers(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> rows(m, INT_MAX);
        std::vector<int> cols(n, INT_MIN);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rows[i] = std::min(rows[i], matrix[i][j]);
                cols[j] = std::max(cols[j], matrix[i][j]);
            }
        }
        std::vector<int> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rows[i] == cols[j]) {
                    result.push_back(matrix[i][j]);
                }
            }
        }
        return result;
    }
};