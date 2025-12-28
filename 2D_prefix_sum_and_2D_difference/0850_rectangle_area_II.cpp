#include <set>
#include <unordered_map>
#include <vector>

/**
 * You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2]
 * denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and
 * (xi2, yi2) are the coordinates of the top-right corner.
 *
 * Calculate the total area covered by all rectangles in the plane. Any area covered by two or more
 * rectangles should only be counted once.
 *
 * Return the total area. Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= rectangles.length <= 200
 * ! rectanges[i].length == 4
 * ! 0 <= xi1, yi1, xi2, yi2 <= 10^9
 * ! xi1 <= xi2
 * ! yi1 <= yi2
 */

class Solution {
public:
    int rectangleArea(std::vector<std::vector<int>>& rectangles)
    {
        constexpr int kMod = 1e9 + 7;
        std::set<int> xCoords;
        std::set<int> yCoords;
        for (const auto& rect : rectangles) {
            xCoords.insert(rect[0]);
            xCoords.insert(rect[2]);
            yCoords.insert(rect[1]);
            yCoords.insert(rect[3]);
        }
        std::unordered_map<int, int> mapX;
        std::unordered_map<int, int> mapY;
        for (auto iter = xCoords.begin(); iter != xCoords.end(); ++iter) {
            mapX[*iter] = std::distance(xCoords.begin(), iter);
        }
        for (auto iter = yCoords.begin(); iter != yCoords.end(); ++iter) {
            mapY[*iter] = std::distance(yCoords.begin(), iter);
        }
        const int m = xCoords.size();
        const int n = yCoords.size();
        // diff[i][j] = z, add z to all elements of matrix[i:m-1][j:n-1]
        std::vector<std::vector<int>> diff(1 + m, std::vector<int>(1 + n, 0));
        for (const auto& rect : rectangles) {
            const int x1 = mapX[rect[0]];
            const int y1 = mapY[rect[1]];
            const int x2 = mapX[rect[2]] - 1;
            const int y2 = mapY[rect[3]] - 1;
            diff[x1][y1] += 1;
            diff[x2 + 1][y1] -= 1;
            diff[x1][y2 + 1] -= 1;
            diff[x2 + 1][y2 + 1] += 1;
        }
        // compute diff[i][j] = sum of matrix[0:i][0:j]
        long long result = 0;
        for (int i = 0; i < m - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if (i > 0) {
                    diff[i][j] += diff[i - 1][j];
                }
                if (j > 0) {
                    diff[i][j] += diff[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    diff[i][j] -= diff[i - 1][j - 1];
                }
                if (diff[i][j] > 0) {
                    const long long height = *std::next(xCoords.begin(), i + 1) - *std::next(xCoords.begin(), i);
                    const long long width = *std::next(yCoords.begin(), j + 1) - *std::next(yCoords.begin(), j);
                    result = (result + height * width % kMod) % kMod;
                }
            }
        }
        return result;
    }
};