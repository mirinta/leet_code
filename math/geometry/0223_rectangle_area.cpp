#include <utility>

/**
 * Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area
 * covered by the two rectangles.
 *
 * The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner
 * (ax2, ay2).
 *
 * The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner
 * (bx2, by2).
 *
 * ! -10^4 <= ax1 <= ax2 <= 10^4
 * ! -10^4 <= ay1 <= ay2 <= 10^4
 * ! -10^4 <= bx1 <= bx2 <= 10^4
 * ! -10^4 <= by1 <= by2 <= 10^4
 */

class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
    {
        const int area1 = (ax2 - ax1) * (ay2 - ay1);
        const int area2 = (bx2 - bx1) * (by2 - by1);
        const int intersectionW = std::min(ax2, bx2) - std::max(ax1, bx1);
        const int intersectionH = std::min(ay2, by2) - std::max(ay1, by1);
        if (intersectionH <= 0 || intersectionW <= 0)
            return area1 + area2;

        return area1 + area2 - intersectionW * intersectionH;
    }
};