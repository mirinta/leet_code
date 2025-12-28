#include <vector>

/**
 * You are given a 2D 0-indexed integer array dimensions.
 *
 * For all indices i, 0 <= i < dimensions.length, dimensions[i][0] represents the length and
 * dimensions[i][1] represents the width of the rectangle i.
 *
 * Return the area of the rectangle having the longest diagonal. If there are multiple rectangles
 * with the longest diagonal, return the area of the rectangle having the maximum area.
 *
 * ! 1 <= dimensions.length <= 100
 * ! dimensions[i].length == 2
 * ! 1 <= dimensions[i][0], dimensions[i][1] <= 100
 */

class Solution {
public:
    int areaOfMaxDiagonal(std::vector<std::vector<int>>& dimensions)
    {
        int maxDiagonalSquare = 0;
        int maxArea = 0;
        for (const auto& dimension : dimensions) {
            const int length = dimension[0];
            const int width = dimension[1];
            const int diagonalSquare = length * length + width * width;
            const int area = length * width;
            if (diagonalSquare > maxDiagonalSquare) {
                maxDiagonalSquare = diagonalSquare;
                maxArea = area;
            } else if (diagonalSquare == maxDiagonalSquare) {
                maxArea = std::max(maxArea, area);
            }
        }
        return maxArea;
    }
};