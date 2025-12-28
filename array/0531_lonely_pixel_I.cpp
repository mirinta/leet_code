#include <vector>

/**
 * Given an m x n picture consisting of black 'B' and white 'W' pixels, return the number of black
 * lonely pixels.
 *
 * A black lonely pixel is a character 'B' that located at a specific position where the same row
 * and same column don't have any other black pixels.
 *
 * ! m == picture.length
 * ! n == picture[i].length
 * ! 1 <= m, n <= 500
 * ! picture[i][j] is 'W' or 'B'.
 */

class Solution {
public:
    int findLonelyPixel(std::vector<std::vector<char>>& picture)
    {
        if (picture.empty() || picture[0].empty())
            return 0;

        const int m = picture.size();
        const int n = picture[0].size();
        std::vector<int> rowSum(m, 0);
        std::vector<int> colSum(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowSum[i] += picture[i][j] == 'B';
                colSum[j] += picture[i][j] == 'B';
            }
        }
        int result = 0;
        for (int i = 0; i < m; ++i) {
            if (rowSum[i] != 1)
                continue;

            for (int j = 0; j < n; ++j) {
                if (colSum[j] == 1 && picture[i][j] == 'B') {
                    result++;
                    break;
                }
            }
        }
        return result;
    }
};
