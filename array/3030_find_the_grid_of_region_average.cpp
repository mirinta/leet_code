#include <vector>

/**
 * You are given a 0-indexed m x n grid image which represents a grayscale image, where image[i][j]
 * represents a pixel with intensity in the range[0..255]. You are also given a non-negative integer
 * threshold.
 *
 * Two pixels image[a][b] and image[c][d] are said to be adjacent if |a - c| + |b - d| == 1.
 *
 * A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent
 * pixels is less than or equal to threshold.
 *
 * All pixels in a region belong to that region, note that a pixel can belong to multiple regions.
 *
 * You need to calculate a 0-indexed m x n grid result, where result[i][j] is the average intensity
 * of the region to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j]
 * belongs to multiple regions, result[i][j] is the average of the rounded down average intensities
 * of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any
 * region, result[i][j] is equal to image[i][j].
 *
 * Return the grid result.
 *
 * ! 3 <= n, m <= 500
 * ! 0 <= image[i][j] <= 255
 * ! 0 <= threshold <= 255
 */

class Solution {
public:
    std::vector<std::vector<int>> resultGrid(std::vector<std::vector<int>>& image, int threshold)
    {
        const int m = image.size();
        const int n = image[0].size();
        result = std::vector<std::vector<int>>(m, std::vector<int>(n, 0));
        count = std::vector<std::vector<int>>(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                helper(i, j, image, threshold);
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (count[i][j] == 0) {
                    result[i][j] = image[i][j];
                } else {
                    result[i][j] /= count[i][j];
                }
            }
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::vector<std::vector<int>> result;
    std::vector<std::vector<int>> count;

    void helper(int topLeftX, int topLeftY, const std::vector<std::vector<int>>& image, int threshold)
    {
        const int m = image.size();
        const int n = image[0].size();
        if (topLeftX + 2 >= m || topLeftY + 2 >= n)
            return;

        int sum = 0;
        for (int i = topLeftX; i <= topLeftX + 2; ++i) {
            for (int j = topLeftY; j <= topLeftY + 2; ++j) {
                sum += image[i][j];
                for (const auto& [dx, dy] : kDirections) {
                    const int x = i + dx;
                    const int y = j + dy;
                    if (x < topLeftX || x > topLeftX + 2 || y < topLeftY || y > topLeftY + 2)
                        continue;

                    if (std::abs(image[i][j] - image[x][y]) > threshold)
                        return;
                }
            }
        }
        for (int i = topLeftX; i <= topLeftX + 2; ++i) {
            for (int j = topLeftY; j <= topLeftY + 2; ++j) {
                result[i][j] += sum / 9;
                count[i][j] += 1;
            }
        }
    }
};