#include <algorithm>
#include <vector>

/**
 * You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns
 * of the matrix in any order.
 *
 * Return the area of the largest submatrix within matrix where every element of the submatrix is 1
 * after reordering the columns optimally.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m * n <= 10^5
 * ! matrix[i][j] is either 0 or 1.
 */

class Solution {
public:
    int largestSubmatrix(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1 && i > 0) {
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
            auto info = matrix[i]; // info[j] = num of consecutive ones of the jth column
            std::sort(info.begin(), info.end(), std::greater());
            for (int k = 0; k < n; ++k) {
                // # <---- height 3
                // # # <-- height 2
                // # #
                // 0 1
                // - at index 0, the max rectangle area = 1x3 = 3
                // - at index 1, the max rectangle area = 2x2 = 4
                // - thus, the max rectangle area = 4
                result = std::max(result, info[k] * (k + 1));
            }
        }
        return result;
    }
};