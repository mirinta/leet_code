#include <vector>

/**
 * You are given an n x n integer matrix. You can do the following operation any number of times:
 *
 * - Choose any two adjacent elements of matrix and multiply each of them by -1.
 *
 * Two elements are considered adjacent if and only if they share a border.
 *
 * Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the
 * matrix's elements using the operation mentioned above.
 *
 * ! n == matrix.length == matrix[i].length
 * ! 2 <= n <= 250
 * ! -10^5 <= matrix[i][j] <= 10^5
 */

class Solution {
public:
    long long maxMatrixSum(std::vector<std::vector<int>>& matrix)
    {
        long long min = LLONG_MAX;
        int count = 0;
        long long sum = 0;
        for (const auto& row : matrix) {
            for (const auto& val : row) {
                sum += std::abs(val);
                count += val < 0;
                min = std::min<long long>(min, std::abs(val));
            }
        }
        if (count % 2 == 0)
            return sum;

        return sum - 2 * min;
    }
};