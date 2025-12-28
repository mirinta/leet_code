#include <unordered_map>
#include <vector>

/**
 * Given a matrix and a target, return the number of non-empty submatrices that sum to target.
 *
 * A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <=
 * y2.
 *
 * Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some
 * coordinate that is different: for example, if x1 != x1'.
 *
 * ! 1 <= matrix.length <= 100
 * ! 1 <= matrix[0].length <= 100
 * ! -1000 <= matrix[i] <= 1000
 * ! -10^8 <= target <= 10^8
 */

class Solution {
public:
    int numSubmatrixSumTarget(std::vector<std::vector<int>>& matrix, int target)
    {
        // presum[i][j] = sum of matrix[0][0] + ... + matrix[i-1][j-1]
        //         y1       y2
        //    0----+----------+
        //    | B  |    A     |
        // x' +----+----------+
        //    | C  |  target  |
        // x  +----+----------+
        //       (x,y1)    (x,y2)
        //
        // target + A = (B+A+C+target) - (B+C) = presum[x+1][y2+1] - presum[x+1][y1]
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> presum(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] + matrix[i - 1][j - 1] - presum[i - 1][j - 1];
            }
        }
        std::unordered_map<int, int> map;
        int result = 0;
        for (int y1 = 0; y1 < n; ++y1) {
            for (int y2 = y1; y2 < n; ++y2) {
                map.clear();
                map[0] = 1;
                for (int x = 0; x < m; ++x) {
                    const int APlusTarget = presum[x + 1][y2 + 1] - presum[x + 1][y1];
                    const int A = APlusTarget - target;
                    if (map.count(A)) {
                        result += map[A];
                    }
                    map[APlusTarget] += 1;
                }
            }
        }
        return result;
    }
};