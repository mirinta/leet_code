#include <algorithm>
#include <vector>

/**
 * You are given an m x n binary matrix image where 0 represents a white pixel and 1 represents a
 * black pixel.
 *
 * The black pixels are connected (i.e., there is only one black region). Pixels are connected
 * horizontally and vertically.
 *
 * Given two integers x and y that represents the location of one of the black pixels, return the
 * area of the smallest (axis-aligned) rectangle that encloses all black pixels.
 *
 * You must write an algorithm with less than O(mn) runtime complexity.
 *
 * ! m == image.length
 * ! n == image[i].length
 * ! 1 <= m, n <= 100
 * ! image[i][j] is either '0' or '1'.
 * ! 0 <= x < m
 * ! 0 <= y < n
 * ! image[x][y] == '1'.
 * ! The black pixels in the image only form one component.
 */

class Solution {
public:
    int minArea(std::vector<std::vector<char>>& image, int x, int y)
    {
        const int m = image.size();
        const int n = image[0].size();
        const int top = findTop(0, x, image);
        const int bottom = findBottom(x, m - 1, image);
        const int left = findLeft(0, y, image);
        const int right = findRight(y, n - 1, image);
        return (bottom - top + 1) * (right - left + 1);
    }

private:
    int findTop(int xmin, int xmax, const std::vector<std::vector<char>>& image)
    {
        int lo = xmin;
        int hi = xmax;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (std::any_of(image[mid].begin(), image[mid].end(), [](const auto& v) { return v == '1'; })) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    int findBottom(int xmin, int xmax, const std::vector<std::vector<char>>& image)
    {
        int lo = xmin;
        int hi = xmax;
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (std::any_of(image[mid].begin(), image[mid].end(), [](const auto& v) { return v == '1'; })) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

    int findLeft(int ymin, int ymax, const std::vector<std::vector<char>>& image)
    {
        int lo = ymin;
        int hi = ymax;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (std::any_of(image.begin(), image.end(), [&](const auto& v) { return v[mid] == '1'; })) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    int findRight(int ymin, int ymax, const std::vector<std::vector<char>>& image)
    {
        int lo = ymin;
        int hi = ymax;
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (std::any_of(image.begin(), image.end(), [&](const auto& v) { return v[mid] == '1'; })) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }
};
