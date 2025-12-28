#include <queue>
#include <vector>

/**
 * 编写函数，实现许多图片编辑软件都支持的「颜色填充」功能。
 *
 * 待填充的图像用二维数组 image 表示，元素为初始颜色值。初始坐标点的行坐标为 sr 列坐标为
 * sc。需要填充的新颜色为 newColor 。
 *
 *「周围区域」是指颜色相同且在上、下、左、右四个方向上存在相连情况的若干元素。
 *
 * 请用新颜色填充初始坐标点的周围区域，并返回填充后的图像。
 *
 * ! image 和 image[0] 的长度均在范围 [1, 50] 内。
 * ! 初始坐标点 (sr,sc) 满足 0 <= sr < image.length 和 0 <= sc < image[0].length 。
 * ! image[i][j] 和 newColor 表示的颜色值在范围 [0, 65535] 内。
 */

class Solution {
public:
    std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor)
    {
        const int m = image.size();
        const int n = image[0].size();
        const int oldColor = image[sr][sc];
        if (oldColor == newColor)
            return image;

        std::queue<std::pair<int, int>> queue;
        queue.emplace(sr, sc);
        image[sr][sc] = newColor;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || image[i][j] != oldColor)
                        continue;

                    image[i][j] = newColor;
                    queue.emplace(i, j);
                    std::printf("%d, %d\n", i, j);
                }
            }
        }
        return image;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};