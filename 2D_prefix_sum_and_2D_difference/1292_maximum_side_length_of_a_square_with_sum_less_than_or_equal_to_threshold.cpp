#include <vector>

/**
 * Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square
 * with a sum less than or equal to threshold or return 0 if there is no such square.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 300
 * ! 0 <= mat[i][j] <= 10^4
 * ! 0 <= threshold <= 10^5
 */

class Solution {
public:
    int maxSideLength(std::vector<std::vector<int>>& mat, int threshold)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        // presum[i][j] = sum of all elements in matrix[0:i-1][0:j-1]
        std::vector<std::vector<long long>> presum(m + 1, std::vector<long long>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
        // guess the final answer
        int lo = 0;
        int hi = std::min(m, n);
        while (lo < hi) {
            const int length = hi - (hi - lo) / 2; // length of the square
            if (isValid(length, m, n, presum, threshold)) {
                lo = length;
            } else {
                hi = length - 1;
            }
        }
        return lo;
    }

private:
    // return sum of all elements in matrix[x1:x2][y1:y2]
    long long query(int x1, int y1, int x2, int y2, const std::vector<std::vector<long long>>& presum)
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

    // check if there exists a square of given length that sum of all its elements <= threshold
    bool isValid(int length, int m, int n, const std::vector<std::vector<long long>>& presum, long long threshold)
    {
        for (int i = 0; i + length - 1 < m; ++i) {
            for (int j = 0; j + length - 1 < n; ++j) {
                if (query(i, j, i + length - 1, j + length - 1, presum) <= threshold)
                    return true;
            }
        }
        return false;
    }
};