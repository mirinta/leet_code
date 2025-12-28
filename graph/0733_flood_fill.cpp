#include <vector>

/**
 * An image is represented by an m x n integer grid image where image[i][j] represents the pixel
 * value of the image.
 *
 * You are also given three integers sr, sc, and color. You should perform a flood fill on the image
 * starting from the pixel image[sr][sc].
 *
 * To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally
 * to the starting pixel of the same color as the starting pixel, plus any pixels connected
 * 4-directionally to those pixels (also with the same color), and so on. Replace the color of all
 * of the aforementioned pixels with color.
 *
 * Return the modified image after performing the flood fill.
 *
 * ! m == image.length
 * ! n == image[i].length
 * ! 1 <= m, n <= 50
 * ! 0 <= image[i][j], color < 2^16
 * ! 0 <= sr < m
 * ! 0 <= sc < n
 */

class Solution {
public:
    std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int color)
    {
        if (image.empty() || image[0].empty())
            return {};

        if (image[sr][sc] == color)
            return image;

        dfs(image, sr, sc, image[sr][sc], color);
        return image;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void dfs(std::vector<std::vector<int>>& image, int x, int y, int target, int newColor)
    {
        const int m = image.size();
        const int n = image[0].size();
        image[x][y] = newColor;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != target)
                continue;

            dfs(image, i, j, target, newColor);
        }
    }
};