#include <vector>

/**
 * There exist n rectangles in a 2D plane. You are given two 0-indexed 2D integer arrays bottomLeft
 * and topRight, both of size n x 2, where bottomLeft[i] and topRight[i] represent the bottom-left
 * and top-right coordinates of the ith rectangle respectively.
 *
 * You can select a region formed from the intersection of two of the given rectangles. You need to
 * find the largest area of a square that can fit inside this region if you select the region
 * optimally.
 *
 * Return the largest possible area of a square, or 0 if there do not exist any intersecting regions
 * between the rectangles.
 *
 * ! n == bottomLeft.length == topRight.length
 * ! 2 <= n <= 10^3
 * ! bottomLeft[i].length == topRight[i].length == 2
 * ! 1 <= bottomLeft[i][0], bottomLeft[i][1] <= 10^7
 * ! 1 <= topRight[i][0], topRight[i][1] <= 10^7
 * ! bottomLeft[i][0] < topRight[i][0]
 * ! bottomLeft[i][1] < topRight[i][1]
 */

class Solution {
public:
    long long largestSquareArea(std::vector<std::vector<int>>& bottomLeft, std::vector<std::vector<int>>& topRight)
    {
        const int n = bottomLeft.size();
        long long maxLength = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (bottomLeft[i][0] >= topRight[j][0] || bottomLeft[j][0] >= topRight[i][0])
                    continue; // no intersection

                if (bottomLeft[i][1] >= topRight[j][1] || bottomLeft[j][1] >= topRight[i][1])
                    continue; // no intersection

                const long long w =
                    std::abs(std::max(bottomLeft[i][0], bottomLeft[j][0]) - std::min(topRight[i][0], topRight[j][0]));
                const long long h =
                    std::abs(std::max(bottomLeft[i][1], bottomLeft[j][1]) - std::min(topRight[i][1], topRight[j][1]));
                maxLength = std::max(maxLength, std::min(h, w));
            }
        }
        return maxLength * maxLength;
    }
};