#include <vector>

/**
 * Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x
 * mat2. You may assume that multiplication is always possible.
 *
 * ! m == mat1.length
 * ! k == mat1[i].length == mat2.length
 * ! n == mat2[i].length
 * ! 1 <= m, n, k <= 100
 * ! -100 <= mat1[i][j], mat2[i][j] <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> multiply(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2)
    {
        // mat1.shape = MxK
        // mat2.shape = KxN
        // result.shape = MxN
        // result[i][j] = sum (mat1[i][p] * mat2[p][j]), p = 0,1,...,k
        const int m = mat1.size();
        const int k = mat1[0].size();
        const int n = mat2[0].size();
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int p = 0; p < k; ++p) {
                if (mat1[i][p] == 0)
                    continue;

                for (int j = 0; j < n; ++j) {
                    if (mat2[p][j] == 0)
                        continue;

                    result[i][j] += mat1[i][p] * mat2[p][j];
                }
            }
        }
        return result;
    }
};
