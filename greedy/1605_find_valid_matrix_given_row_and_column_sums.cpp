#include <vector>

/**
 * You are given two arrays rowSum and colSum of non-negative integers where rowSum[i] is the sum of
 * the elements in the ith row and colSum[j] is the sum of the elements of the jth column of a 2D
 * matrix. In other words, you do not know the elements of the matrix, but you do know the sums of
 * each row and column.
 *
 * Find any matrix of non-negative integers of size rowSum.length x colSum.length that satisfies the
 * rowSum and colSum requirements.
 *
 * Return a 2D array representing any matrix that fulfills the requirements. It's guaranteed that at
 * least one matrix that fulfills the requirements exists.
 *
 * ! 1 <= rowSum.length, colSum.length <= 500
 * ! 0 <= rowSum[i], colSum[i] <= 10^8
 * ! sum(rowSum) == sum(colSum)
 */

class Solution {
public:
    std::vector<std::vector<int>> restoreMatrix(std::vector<int>& rowSum, std::vector<int>& colSum)
    {
        const int m = rowSum.size();
        const int n = colSum.size();
        std::vector<std::vector<int>> result(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int min = std::min(rowSum[i], colSum[j]);
                result[i][j] = min;
                rowSum[i] -= min;
                colSum[j] -= min;
            }
        }
        return result;
    }
};