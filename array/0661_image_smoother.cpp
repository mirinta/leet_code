#include <cmath>
#include <vector>

/**
 * An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by
 * rounding down the average of the cell and the eight surrounding cells (i.e., the average of the
 * nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not
 * present, we do not consider it in the average (i.e., the average of the four cells in the red
 * smoother).
 *
 * Given an m x n integer matrix img representing the grayscale of an image, return the image after
 * applying the smoother on each cell of it.
 *
 * ! m == img.length
 * ! n == img[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= img[i][j] <= 255
 */

class Solution {
public:
    std::vector<std::vector<int>> imageSmoother(std::vector<std::vector<int>>& img)
    {
        const int m = img.size();
        const int n = img[0].size();
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = average(i, j, img);
            }
        }
        return result;
    }

private:
    int average(int x, int y, const std::vector<std::vector<int>>& image)
    {
        const int m = image.size();
        const int n = image[0].size();
        int sum = 0;
        int count = 0;
        for (const auto& dx : {-1, 0, 1}) {
            for (const auto& dy : {-1, 0, 1}) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                sum += image[i][j];
                count++;
            }
        }
        return std::floor(sum * 1.0 / count);
    }
};